#include "input_def.hpp"

namespace ykm::input
{

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS mouse_evt
const ykm::enum_map<mouse_evt, 16>
    mouse_evt_map(YKM_ENUM_MAP_BUILD(YKM_APP_SYS_MOUSE_EVT_ELEM, none));

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS keycode
const ykm::enum_map<keycode, 256> keycode_map(YKM_ENUM_MAP_BUILD(YKM_APP_SYS_KEYCODE_ELEM, none));

} // namespace ykm::input
