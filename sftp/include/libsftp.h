#ifndef LIBSFTP_H
#define LIBSFTP_H

#ifdef __cplusplus
#define LIBSFTP_C extern "C"
#else
#define LIBSFTP_C
#endif

#ifdef LIBSFTP_SHARED_BUILD

#ifdef _WIN32
#define LIBSFTP_EXPORT __declspec(dllexport)
#else
#define LIBSFTP_EXPORT __attribute__((visibility("default")))
#endif

#else
#define LIBSFTP_EXPORT
#endif

#define LIBSFTP_API(r) LIBSFTP_C LIBSFTP_EXPORT r

typedef void* SFTP_connect_handle;

typedef struct
{
    void* p;
}SFTP_async_handle;
typedef struct
{
    void* p;
} SFTP_async_con;

#define LIBSFTP_RESULT LIBSFTP_API(LibsftpResult)
#define LIBSFTP_HANDLE LIBSFTP_API(SFTP_connect_handle)

typedef struct
{
    int code;
    const char* msg;
} LibsftpResult;

LIBSFTP_API(void*) SFTP_init();
LIBSFTP_API(const char*) SFTP_get_init_error(void* handle);
LIBSFTP_API(void) SFTP_exit(void* handle);

LIBSFTP_API(SFTP_connect_handle) SFTP_connect_remote(const char* hostname, int port, const char* username, const char* password);

LIBSFTP_RESULT SFTP_valid_connection(SFTP_connect_handle handler);

LIBSFTP_API(void) SFTP_close_connection(SFTP_connect_handle handler);

LIBSFTP_RESULT SFTP_upload_file(SFTP_connect_handle handler, const char* local, const char* remote);
LIBSFTP_RESULT SFTP_download_file(SFTP_connect_handle handler, const char* local, const char* remote);
LIBSFTP_RESULT SFTP_execute_command(SFTP_connect_handle handler, const char* cmd);

typedef struct
{
    int state;
    int code;
    const char* msg;
} SFTP_async_result;

LIBSFTP_API(SFTP_async_handle) SFTP_make_async_handle();
LIBSFTP_API(void) SFTP_del_async_handle(SFTP_async_handle ah);
LIBSFTP_RESULT SFTP_err_async_handle(SFTP_async_handle ah);
LIBSFTP_API(SFTP_async_con) SFTP_async_start(SFTP_async_handle ah, const char* hostname, int port, const char* username, const char* password);

LIBSFTP_API(void) SFTP_async_upload(SFTP_async_con ac, const char* local, const char* remote);
LIBSFTP_API(void) SFTP_async_down(SFTP_async_con ac, const char* local, const char* remote);
LIBSFTP_API(SFTP_async_result) SFTP_async_state(SFTP_async_con ac);
LIBSFTP_API(void) SFTP_async_close(SFTP_async_con ac);

#endif
