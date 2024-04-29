#ifndef YKM_SOCKET_HPP
#define YKM_SOCKET_HPP

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif

#include <string>

namespace ykm
{

inline int socket_init()
{
#ifdef _WIN32
    ::WSADATA wsaData;
    return ::WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif // _WIN32

    return 0;
}

inline void socket_exit()
{
#ifdef _WIN32
    ::WSACleanup();
#endif
}

struct tcpsocket
{
    struct result final
    {
        int code;
        std::string msg;
    };
    tcpsocket(){};
    result connect(const char* ip, int port)
    {

#ifdef _WIN32
        sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET)
        {
            return {-1, "INVALID_SOCKET"};
        }

        ::SOCKADDR_IN serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip);
        serverAddr.sin_port = htons(port);
        int result =
            ::connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
#else
#endif
        init = true;
        return {0, "Success"};
    }

    void close()
    {
        init = false;
#ifdef _WIN32
        ::closesocket(sock);
#else
#endif
    }

    ~tcpsocket()
    {
        if (init)
        {
            close();
        }
    }

    auto& get() { return sock; }

  private:
#ifdef WIN32
    ::SOCKET sock;
    bool init = false;
#endif
};

} // namespace ykm

#endif
