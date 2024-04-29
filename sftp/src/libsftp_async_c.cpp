#include "libsftp.h"

#include <format>
#include <vector>

#include "libsftp.hpp"
#include "ykm_opt.hpp"
#include "ykm_thread_tool.hpp"

typedef ykm::SSH_Handler::Result Result;

inline char* split_args(char* args, int len, int index)
{
    int find = 0;
    int i = 1;
    char* addr = args;
    while (find != index && i < len)
    {
        if (args[i] == '\0' and (i + 1 < len))
        {
            find += 1;
            addr = &args[i + 1];
        }
    }
    return addr;
}

struct TaskMsg final
{
    int state;
    int code;
    std::string msg;
};

struct TaskEvent final
{
    int method;
    std::vector<char> buffer;
};

#define AH ((AsyncHandle*)ah.p)
#define AC ((AsyncCon*)ac.p)
struct AsyncCon;

struct AsyncHandle final
{
    std::vector<AsyncCon*> cons;
    Result init_res;
    AsyncHandle()
    {
        init_res.code = 0;
        int err = ykm::socket_init();
        init_res = Result{err, std::format("socket init failed, code: {}", err)};
        if (init_res.code == 0)
        {
            init_res = ykm::InitSSHModule();
        }
    }
    ~AsyncHandle()
    {
        ykm::socket_exit();
        ykm::ExitSSHModule();
    }
};

struct AsyncCon final
{
    AsyncHandle* ah;
    int id;
    bool login = false;
    ykm::LockQueue<TaskMsg> msgs;
    ykm::LockQueue<TaskEvent> events;
    std::atomic<bool> exit;
    std::thread thr;

    TaskMsg last_output;
    void task()
    {
        login = false;
        ykm::Opt<ykm::SSH_Handler> sh;

        while (!exit)
        {
            auto evt = events.pop();
            TaskMsg msg;
            switch (evt.method)
            {
            case 100: // login
            {
                auto info = DecodeLogin(evt.buffer.data());
                sh.construct(info.hostname, info.port, info.username, info.password);
                auto res = sh->get_conenct_res();
                msg.state = res.code ? -1 : 200;
                msg.code = res.code;
                msg.msg = res.msg;
            }
            break;
            case 1: // upload
            {
                auto local = split_args(evt.buffer.data(), evt.buffer.size(), 0);
                auto remote = split_args(evt.buffer.data(), evt.buffer.size(), 1);
                auto res = sh->upload_file(local, remote);
                msg.state = res.code ? 2 : 1;
                msg.code = res.code;
                msg.msg = res.msg;
            }
            break;
            case 0: // all done
                msg.state = 0;
                msg.code = 0;
                msg.msg = "task done";
            }

            if (msg.state < 1)
            {
                exit = true;
            }
            msgs.push(std::move(msg));
        }

        if (sh)
            sh.destruct();
    }

    static std::vector<char> EncodeLogin(const char* hostname, int port, const char* username, const char* password)
    {
        int size = sizeof(int) * 4;
        int len_1 = strlen(hostname);
        int len_3 = strlen(username);
        int len_4 = strlen(password);
        size += len_1 + len_3 + len_4;

        std::vector<char> buffer;
        buffer.resize(size);
        int o = 0;
        memcpy(&buffer[0], &len_1, sizeof(int));
        memcpy(&buffer[(o += sizeof(int))], hostname, len_1);
        memcpy(&buffer[(o += len_1)], &port, sizeof(int));
        memcpy(&buffer[(o += sizeof(int))], &len_3, sizeof(int));
        memcpy(&buffer[(o += sizeof(int))], username, len_3);
        // memcpy(&buffer[(o+=len_3)], &len_4, sizeof(int));
        memcpy(&buffer[(o += len_3)], password, len_4);
        return buffer;
    }

    struct LoginInfo
    {
        const char* hostname;
        int port;
        const char* username;
        const char* password;
    };

    static LoginInfo DecodeLogin(const char* buffer)
    {
        LoginInfo info;
        int len = 0;
        int o = sizeof(int);
        info.hostname = &buffer[o + sizeof(int)];

        memcpy(&len, buffer, sizeof(int));
        o += len;

        memcpy(&info.port, &buffer[o], sizeof(int));
        memcpy(&len, &buffer[(o += sizeof(int))], sizeof(int));
        info.username = &buffer[(o += sizeof(int))];
        info.password = &buffer[(o += len)];
        return info;
    }

    AsyncCon(const char* hostname, int port, const char* username, const char* password) : thr(&AsyncCon::task, this)
    {
        last_output.state = 100;                                             // wait login
        events.push({100, EncodeLogin(hostname, port, username, password)}); // login
        thr.detach();
    }
};

inline void RemoveAsyncCon(AsyncCon* ac)
{
    auto& cons = ac->ah->cons;
    auto back = cons.back();
    auto ca = back;
    back->id = ac->id;
    ac->id = -1;
    cons[ac->id] = back;
    delete ac;
    cons.pop_back();
}

// async api
LIBSFTP_API(SFTP_async_handle) SFTP_make_async_handle() { return {new AsyncHandle()}; }
LIBSFTP_API(void) SFTP_del_async_handle(SFTP_async_handle ah) { delete AH; }

LIBSFTP_RESULT SFTP_err_async_handle(SFTP_async_handle ah) { return {AH->init_res.code, AH->init_res.code ? AH->init_res.msg.c_str() : nullptr}; }

LIBSFTP_API(SFTP_async_con) SFTP_async_start(SFTP_async_handle ah, const char* hostname, int port, const char* username, const char* password)
{
    AsyncCon* ac = new AsyncCon(hostname, port, username, password);
    ac->ah = AH;
    ac->id = AH->cons.size();
    AH->cons.push_back(ac);
    return {ac};
}

LIBSFTP_API(void) SFTP_async_upload(SFTP_async_con ac, const char* local, const char* remote)
{
    int len = strlen(local);
    int len2 = strlen(remote);
    TaskEvent evt;
    evt.method = 1;
    evt.buffer.resize(len + len2);
    memcpy(&evt.buffer[0], local, len);
    memcpy(&evt.buffer[len], remote, len2);
    AC->events.push(std::move(evt));
}

LIBSFTP_API(void) SFTP_async_done(SFTP_async_con ac)
{
    TaskEvent evt;
    evt.method = 0;
    AC->events.push(std::move(evt));
}

LIBSFTP_API(SFTP_async_result) SFTP_async_state(SFTP_async_con ac)
{
    AC->msgs.try_pop(AC->last_output);
    return {AC->last_output.state, AC->last_output.code, AC->last_output.msg.c_str()};
}

LIBSFTP_API(void) SFTP_async_close(SFTP_async_con ac)
{
    auto& cons = AC->ah->cons;
    auto back = cons.back();
    auto ca = back;
    back->id = AC->id;
    cons[AC->id] = back;
    delete AC;
    cons.pop_back();
}
