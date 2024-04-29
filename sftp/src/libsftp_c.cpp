#include "libsftp.hpp"
#include "libsftp.h"
#include <format>

typedef ykm::SSH_Handler::Result Result;

void* SFTP_init()
{
    if (int err = ykm::socket_init())
    {
        return new Result{err, std::format("socket init failed, code: {}", err)};
    }
    auto res = new Result(ykm::InitSSHModule());
    return res;
}

LIBSFTP_API(const char*) SFTP_get_init_error(void* handle)
{
    auto res = (Result*)handle;
    return res->msg.c_str();
}

LIBSFTP_API(void) SFTP_exit(void* handle)
{
    delete ((Result*)handle);
    ykm::ExitSSHModule();
    ykm::socket_exit();
}

#define SSH_C ((CHanlder*)handler)

struct CHanlder
{
    ykm::SSH_Handler h;
    Result up;
    Result dl;
    Result cm;
};

LIBSFTP_API(SFTP_connect_handle) SFTP_connect_remote(const char* hostname, int port, const char* username, const char* password)
{
    return new CHanlder{ykm::SSH_Handler(hostname, port, username, password)};
}

LIBSFTP_RESULT SFTP_valid_connection(SFTP_connect_handle handler)
{
    auto res = SSH_C->h.get_conenct_res();
    return {res.code, res.code == 0 ? nullptr : res.msg.c_str()};
}

LIBSFTP_API(void) SFTP_close_connection(SFTP_connect_handle handler) { delete SSH_C; }

LIBSFTP_RESULT SFTP_upload_file(SFTP_connect_handle handler, const char* local, const char* remote)
{
    SSH_C->up = SSH_C->h.upload_file(local, remote);
    return {SSH_C->up.code, SSH_C->up.code == 0 ? nullptr : SSH_C->up.msg.c_str()};
}

LIBSFTP_RESULT SFTP_download_file(SFTP_connect_handle handler, const char* local, const char* remote)
{
    SSH_C->dl = SSH_C->h.download_file(local, remote);
    return {SSH_C->dl.code, SSH_C->dl.code == 0 ? nullptr : SSH_C->dl.msg.c_str()};
}

LIBSFTP_RESULT SFTP_execute_command(SFTP_connect_handle handler, const char* cmd)
{
    SSH_C->cm = SSH_C->h.execute_cmd(cmd);
    return {SSH_C->cm.code, SSH_C->cm.code == 0 ? nullptr : SSH_C->cm.msg.c_str()};
}
