/*
    system api wrap
    dev 0.0.1
*/

#ifndef YKM_APP_SYS_H
#define YKM_APP_SYS_H

#include "base.h"
#include "app.h"

YKM_APP_CAPI
void YkmSys_SetGPool(YkmApp_GPool gpool);

//*****************************************//
//********** base system api 1.0 **********//

struct YkmSys_ScreenInfo
{
    int x;
    int y;

    int width;
    int height;

    int rate;

    int dpiX;
    int dpiY;

    int id;
};

YKM_APP_CAPI
YkmSys_ScreenInfo* YkmSys_GetScreenInfo(int* num);

// TODO get system fonts resources
typedef struct
{

} YkmSys_FontInfo;

// TODO get system device info -> cpu gpu memory disk

//********** base system api 1.0 **********//
//*****************************************//



//***************************//
//********** input **********//

typedef int (*YkmSys_InputCodeParser)(const void*, const char*);
typedef const char* (*YkmSys_InputCodeMapper)(const void*, int);

struct YkmSys_InputMap
{
    int mapId;
    const void* _ph;
    YkmSys_InputCodeParser parser;
    YkmSys_InputCodeMapper mapper;
};

#define YKM_SYS_Input_MapId_Keycode 0
#define YKM_SYS_Input_MapId_MouseEvt 1

YKM_APP_CAPI
YkmSys_InputMap YkmSys_GetInputMap(int mapId);

//********** input **********//
//***************************//

#endif
