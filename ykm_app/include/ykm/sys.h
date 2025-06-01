/*
    system api wrap
    dev 0.0.1
*/

#ifndef YKM_APP_SYS_H
#define YKM_APP_SYS_H

#include "base.h"
#include "app.h"

YKM_APP_CAPI
void YkmApp_SetGPool(YkmApp_GPool gpool);

//*****************************************//
//********** base system api 1.0 **********//

struct YkmApp_ScreenInfo
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
YkmApp_ScreenInfo* YkmApp_GetScreenInfo(int* num);

// TODO get system fonts resources
typedef struct
{

} YkmApp_FontInfo;

// TODO get system device info -> cpu gpu memory disk

//********** base system api 1.0 **********//
//*****************************************//



//***************************//
//********** input **********//

typedef int (*YkmApp_InputCodeParser)(const void*, const char*);
typedef const char* (*YkmApp_InputCodeMapper)(const void*, int);

struct YkmApp_InputMap
{
    int mapId;
    const void* _ph;
    YkmApp_InputCodeParser parser;
    YkmApp_InputCodeMapper mapper;
};

#define YKM_SYS_Input_MapId_Keycode 0
#define YKM_SYS_Input_MapId_MouseEvt 1

YKM_APP_CAPI
YkmApp_InputMap YkmApp_GetInputMap(int mapId);

//********** input **********//
//***************************//

#endif
