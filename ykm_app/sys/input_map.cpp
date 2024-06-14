#include "ykm/sys/input_def.hpp"

#include "ykm/sys.h"

namespace ykm::input
{

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS mouse_evt
YKM_SYS_API
const ykm::enum_map<mouse_evt, 16> mouseEvtMap(YKM_ENUM_MAP_BUILD(YKM_APP_SYS_MOUSE_EVT_ELEM, none));

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS keycode
YKM_SYS_API
const ykm::enum_map<keycode, 256> keyCodeMap(YKM_ENUM_MAP_BUILD(YKM_APP_SYS_KEYCODE_ELEM, none));

} // namespace ykm::input

template <typename E, size_t S>
static void WrapMap(const ykm::enum_map<E, S>& i, YkmSys_InputMap& o)
{
    o._ph = &i;
    o.parser = [](const void* _ph, const char* str) { //
        return (int)(((const ykm::enum_map<E, S>*)_ph)->by_name(str));
    };

    o.mapper = [](const void* _ph, int code) { //
        return (((const ykm::enum_map<E, S>*)_ph)->by_code(E(code)));
    };
}

YKM_SYS_CAPI
YkmSys_InputMap YkmSys_GetInputMap(int code)
{
    using namespace ykm::input;
    YkmSys_InputMap map = {code, nullptr, nullptr, nullptr};

    switch (code)
    {
    case YKM_SYS_Input_MapId_Keycode:
        WrapMap(keyCodeMap, map);
        break;

    case YKM_SYS_Input_MapId_MouseEvt:
        WrapMap(mouseEvtMap, map);
        break;
    }
    return map;
}
