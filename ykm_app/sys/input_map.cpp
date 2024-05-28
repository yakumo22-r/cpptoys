#include "input_def.hpp"
#include <ykm/enum_map_macro.h>

namespace ykm::input
{

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS btncode
const ykm::enum_map<btncode, 16> btncode_map = {YKM_APP_SYS_BTNCODE_ELEM};

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS keycode
const ykm::enum_map<keycode, 256> keycode_map = {YKM_APP_SYS_KEYCODE_ELEM};

} // namespace ykm::input
