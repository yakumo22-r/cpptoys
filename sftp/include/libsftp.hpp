#ifndef YKM_LIBSFTP_HPP
#define YKM_LIBSFTP_HPP

#include "socket.hpp"
#include <cstring>

namespace ykm
{

struct SSH_Handler final
{
  public:
    struct Result
    {
        int code;
        std::string msg;
    };
    SSH_Handler(const char* ip, int port, const char* username, const char* password);
    ~SSH_Handler();

    const Result& get_conenct_res()const;
    Result upload_file(const char* local, const char* remote);
    Result download_file(const char* local, const char* remote);
    bool exsits_dir(const char* remote_path);
    Result azure_dir(char* remote_path, int len);

    Result azure_dir(const char* remote_path){
        int len = strlen(remote_path);
        char* buffer = new char[len];
        memcpy(buffer, remote_path, len);

        auto res = azure_dir(buffer, len);

        delete [] buffer;
        return res;
    }

    Result execute_cmd(const char* cmd);
    void disconnect();

  private:
    SocketTcp sock;
    Result connection;
    void* session = nullptr;
    void* sftp = nullptr;
    void* channel = nullptr;

    bool sockOk = false;
    bool authed = false;
    bool startUp = false;
    bool connected = false;
};
SSH_Handler::Result InitSSHModule();
void ExitSSHModule();

} // namespace ykm

#endif
