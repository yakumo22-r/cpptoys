#include "input_def.hpp"

namespace ykm::input
{

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS btncode
const ykm::enum_map<btncode, 16> btncode_map(YKM_ENUM_MAP_BUILD(YKM_APP_SYS_BTNCODE_ELEM, none));

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS keycode
const ykm::enum_map<keycode, 256> keycode_map(YKM_ENUM_MAP_BUILD(YKM_APP_SYS_KEYCODE_ELEM, none));

} // namespace ykm::input
