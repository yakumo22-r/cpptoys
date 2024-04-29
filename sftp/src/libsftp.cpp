#include "libsftp.h"
#include "socket.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <format>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include <libssh2.h>
#include <libssh2_publickey.h>
#include <libssh2_sftp.h>
#include <thread>

#include "libsftp.hpp"
#include "ykm_thread_tool.hpp"

typedef ykm::SSH_Handler::Result Result;

namespace ykm
{

Result InitSSHModule()
{
    int rc = libssh2_init(0);
    if (rc != 0)
    {
        return {rc, "Failed to initialize libssh2"};
    }
    return {0, ""};
}

void ExitSSHModule() { libssh2_exit(); }

#define m_session ((LIBSSH2_SESSION*)(this->session))
#define m_channel ((LIBSSH2_CHANNEL*)(this->channel))
#define m_sftp ((LIBSSH2_SFTP*)(this->sftp))

SSH_Handler::~SSH_Handler()
{
    if (channel)
        libssh2_channel_free(m_channel);

    if (sftp)
        libssh2_sftp_shutdown(m_sftp);

    if (startUp and !authed)
        libssh2_session_disconnect(m_session, "Authentication failed");

    if (session)
        libssh2_session_free(m_session);
}

SSH_Handler::SSH_Handler(const char* ip, int port, const char* username, const char* password)
{

    if (connected)
    {
        connection = {1, "Warn: Already has connection"};
        return;
    }
    session = libssh2_session_init();
    if (!session)
    {
        connection = {-1, "Failed to create a new SSH session"};
        return;
    }

    libssh2_session_set_blocking(m_session, 1);

    auto sock_res = sock.connect(ip, port);
    if (sock_res.code != 0)
    {
        connection = {sock_res.code, sock_res.msg};
        return;
    }
    sockOk = true;

    if (int rc = libssh2_session_startup(m_session, sock.get()))
    {
        connection = {rc, "Failed to establish SSH session"};
        return;
    }
    startUp = true;

    // Load the private key from the SSH config file
    if (int rc = libssh2_userauth_password(m_session, username, password))
    {
        connection = {rc, "Authentication failed"};
        return;
    }
    authed = true;

    sftp = libssh2_sftp_init(m_session);
    if (!sftp)
    {
        connection = {-3, "Failed to initialize SFTP session"};
        return;
    }
    connected = true;
    connection = {0, "success"};
}

const Result& SSH_Handler::get_conenct_res() const { return connection; }

inline int index_last_of_splash(const char* c, int len)
{
    for (int i = len - 2; i >= 0; --i)
    {
        if (c[i] == '/' or c[i] == '\\')
        {
            return i;
        }
    }
    return -1;
}

Result SSH_Handler::upload_file(const char* local, const char* remote)
{
    char buffer[1024];

    int str_size = strlen(remote);
    str_size = index_last_of_splash(remote, str_size);

    Result result;
    result.code = 0;

    if (str_size >= sizeof(buffer))
    {
        char* mBuffer = (char*)malloc(str_size + 1);
        memcpy(mBuffer, remote, str_size);

        mBuffer[str_size] = '\0';
        result = azure_dir(mBuffer, str_size + 1);
        free(mBuffer);
    }
    else
    {
        memcpy(buffer, remote, str_size);
        buffer[str_size] = '\0';
        result = azure_dir(buffer, str_size + 1);
    }

    if (result.code != 0)
        return result;

    FILE* f = fopen(local, "rb");
    if (f)
    {
        std::string res;
        int code = 0;
        LIBSSH2_SFTP_HANDLE* sftp_handle =
            libssh2_sftp_open(m_sftp, remote, LIBSSH2_FXF_WRITE | LIBSSH2_FXF_CREAT | LIBSSH2_FXF_TRUNC, LIBSSH2_SFTP_S_IRUSR | LIBSSH2_SFTP_S_IWUSR);
        if (sftp_handle)
        {
            size_t nbytes;
            while ((nbytes = fread(buffer, 1, sizeof(buffer), f)) > 0)
            {
                libssh2_sftp_write(sftp_handle, buffer, nbytes);
            }

            // Close the file handle
            libssh2_sftp_close(sftp_handle);
        }
        else
        {
            code = libssh2_session_last_errno(m_session);
            res = std::format("Failed to open the remote file {} for writing , err: {}", remote, code);
        }

        fclose(f);
        return {code, res};
    }
    else
    {
        return {-99, std::format("Failed to open the remote file {} for reading", local)};
    }
}

Result SSH_Handler::download_file(const char* local, const char* remote) { return {-1, "no implementation"}; }

bool SSH_Handler::exsits_dir(const char* remote_path) { return libssh2_sftp_opendir(m_sftp, remote_path) != nullptr; }

Result SSH_Handler::azure_dir(char* remote_path, int len)
{
    int now_len = len;

    std::stack<int> node;
    LIBSSH2_SFTP_HANDLE* h = nullptr;
    while (!(h = libssh2_sftp_opendir(m_sftp, remote_path)))
    {
        if ((now_len = index_last_of_splash(remote_path, now_len)) > 0)
        {

            remote_path[now_len] = '\0';
            node.push(now_len + 1);
        }
        else
        {
            break;
        }
    }
    if (h)
    {
        libssh2_sftp_close(h);
    }

    int rc = 0;
    while (node.size() > 0)
    {
        int index = node.top();
        node.pop();
        remote_path[index - 1] = '/';
        rc = libssh2_sftp_mkdir(m_sftp, remote_path, -1);
        if (rc != 0)
        {
            break;
        }
    }

    Result result;
    result.code = rc;
    if (rc != 0)
    {
        result.msg = std::format("mkdir failed path: {} code: ", remote_path, rc);
    }

    return result;
};

Result SSH_Handler::execute_cmd(const char* cmd)
{
    auto channel = libssh2_channel_open_session(m_session);
    if (!channel)
    {
        int code = libssh2_session_last_errno(m_session);
        return {code, std::format("Failed to initalize SFTP session, code: {}", code)};
    }

    libssh2_channel_exec(channel, cmd);

    char buffer[1024];
    std::ostringstream oss;
    while (libssh2_channel_read(channel, buffer, sizeof(buffer)) > 0)
    {
        oss << buffer;
    }

    int ret = libssh2_channel_get_exit_status(channel);

    libssh2_channel_close(channel);
    libssh2_channel_free(channel);
    return {ret, oss.str()};
}

} // namespace ykm

