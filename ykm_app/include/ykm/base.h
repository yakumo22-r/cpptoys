#ifndef YKM_APP_UTILS_API_H
#define YKM_APP_UTILS_API_H

//********************************************//
//********* start of compile flags ***********//
#ifdef __cplusplus
#define YKM_APP_WRAP_C extern "C"
#else
#define YKM_APP_WRAP_C
#endif

#ifdef _WIN32
#define YKM_APP_EXPORT __declspec(dllexport)
#else
#define YKM_APP_EXPORT __attribute__((visibility("default")))
#endif

#ifdef _WIN32
#define YKM_APP_IMPORT __declspec(dllimport)
#else
#define YKM_APP_IMPORT
#endif
//********* end of compile flags ************//
//*******************************************//

typedef const char* YkmApp_ErrBuffer;
typedef void* YkmApp_GPool;

#define YkmApp_False 0
#define YkmApp_True 1

#define YkmApp_R_Ok 0
#define YkmApp_R_Quit 2
#define YkmApp_R_InternalError -1
#define YkmApp_R_Uninitialized -2
#define YkmApp_R_Redefined -3
typedef short YkmApp_Result;
typedef char YkmApp_Bool;

#endif
