#include "input_def.hpp"

// clang-format off

#define YKM_ENUM_MAP(space, value) \
    {                              \
        space::value, #value       \
    }

namespace ykm::input
{

const ykm::enum_map<btncode, 16>& btncode_map()
{
    static ykm::enum_map<btncode, 16> map = 
    {{
        YKM_ENUM_MAP(btncode, invalid),
        YKM_ENUM_MAP(btncode, left),
        YKM_ENUM_MAP(btncode, right),
        YKM_ENUM_MAP(btncode, middle),
        YKM_ENUM_MAP(btncode, M1),
        YKM_ENUM_MAP(btncode, M2),
        YKM_ENUM_MAP(btncode, M3),
        YKM_ENUM_MAP(btncode, M4),
        YKM_ENUM_MAP(btncode, M5),
        YKM_ENUM_MAP(btncode, M6),
        YKM_ENUM_MAP(btncode, M7),
        YKM_ENUM_MAP(btncode, M8),
        YKM_ENUM_MAP(btncode, M9),
        YKM_ENUM_MAP(btncode, M10),
        YKM_ENUM_MAP(btncode, M11),
        YKM_ENUM_MAP(btncode, M12),
        YKM_ENUM_MAP(btncode, M13),
        YKM_ENUM_MAP(btncode, M14),
        YKM_ENUM_MAP(btncode, M15),
    }};
    return map;
}

const ykm::enum_map<keycode, 256>& keycode_map()
{
    static ykm::enum_map<keycode, 256> map = 
    {{
        YKM_ENUM_MAP(keycode, invalid),
        YKM_ENUM_MAP(keycode, backspace ),
        YKM_ENUM_MAP(keycode, tab ),
        YKM_ENUM_MAP(keycode, enter ),
        YKM_ENUM_MAP(keycode, shift ),
        YKM_ENUM_MAP(keycode, ctrl ),
        YKM_ENUM_MAP(keycode, alt ),
        YKM_ENUM_MAP(keycode, pausebreak ),
        YKM_ENUM_MAP(keycode, capslock ),

        YKM_ENUM_MAP(keycode, esc ),

        YKM_ENUM_MAP(keycode, space ),
        YKM_ENUM_MAP(keycode, pageup ),
        YKM_ENUM_MAP(keycode, pagedown ),
        YKM_ENUM_MAP(keycode, end ),
        YKM_ENUM_MAP(keycode, home ),
        YKM_ENUM_MAP(keycode, left ),
        YKM_ENUM_MAP(keycode, up ),
        YKM_ENUM_MAP(keycode, right ),
        YKM_ENUM_MAP(keycode, down ),

        YKM_ENUM_MAP(keycode, insert ),
        YKM_ENUM_MAP(keycode, del ),

        {keycode::_0,"0" },
        {keycode::_1,"1" },
        {keycode::_2,"2" },
        {keycode::_3,"3" },
        {keycode::_4,"4" },
        {keycode::_5,"5" },
        {keycode::_6,"6" },
        {keycode::_7,"7" },
        {keycode::_8,"8" },
        {keycode::_9,"9" },

        // A-Z keycode.
        YKM_ENUM_MAP(keycode,A ),
        YKM_ENUM_MAP(keycode,B ),
        YKM_ENUM_MAP(keycode,C ),
        YKM_ENUM_MAP(keycode,D ),
        YKM_ENUM_MAP(keycode,E ),
        YKM_ENUM_MAP(keycode,H ),
        YKM_ENUM_MAP(keycode,I ),
        YKM_ENUM_MAP(keycode,J ),
        YKM_ENUM_MAP(keycode,K ),
        YKM_ENUM_MAP(keycode,L ),
        YKM_ENUM_MAP(keycode,M ),
        YKM_ENUM_MAP(keycode,N ),
        YKM_ENUM_MAP(keycode,O ),
        YKM_ENUM_MAP(keycode,P ),
        YKM_ENUM_MAP(keycode,Q ),
        YKM_ENUM_MAP(keycode,R ),
        YKM_ENUM_MAP(keycode,S ),
        YKM_ENUM_MAP(keycode,T ),
        YKM_ENUM_MAP(keycode,U ),
        YKM_ENUM_MAP(keycode,V ),
        YKM_ENUM_MAP(keycode,W ),
        YKM_ENUM_MAP(keycode,X ),
        YKM_ENUM_MAP(keycode,Y ),
        YKM_ENUM_MAP(keycode,Z ),
        YKM_ENUM_MAP(keycode,super),

        {keycode::np_0,"numpad0"},
        {keycode::np_1,"numpad1"},
        {keycode::np_2,"numpad2"},
        {keycode::np_3,"numpad3"},
        {keycode::np_4,"numpad4"},
        {keycode::np_5,"numpad5"},
        {keycode::np_6,"numpad6"},
        {keycode::np_7,"numpad7"},
        {keycode::np_8,"numpad8"},
        {keycode::np_9,"numpad9"},

        {keycode::np_mul,       "numpad(*)"},
        {keycode::np_plus,      "numpad(+)"},
        {keycode::np_enter,     "numpad(enter)"},
        {keycode::np_minus,     "numpad(-)"},
        {keycode::np_dot,       "numpad(.)"},
        {keycode::np_divide,    "numpad(/)"},

        YKM_ENUM_MAP(keycode,F1 ),
        YKM_ENUM_MAP(keycode,F2 ),
        YKM_ENUM_MAP(keycode,F3 ),
        YKM_ENUM_MAP(keycode,F4 ),
        YKM_ENUM_MAP(keycode,F5 ),
        YKM_ENUM_MAP(keycode,F6 ),
        YKM_ENUM_MAP(keycode,F7 ),
        YKM_ENUM_MAP(keycode,F8 ),
        YKM_ENUM_MAP(keycode,F9 ),
        YKM_ENUM_MAP(keycode,F10),
        YKM_ENUM_MAP(keycode,F11),
        YKM_ENUM_MAP(keycode,F12),

        {keycode::l_shift, "l-shift" },
        {keycode::r_shift, "r-shift" },
        {keycode::l_ctrl,  "l-ctrl" },
        {keycode::r_ctrl,  "r-ctrl" },
        {keycode::l_alt,   "l-alt" },
        {keycode::r_alt,   "r-alt" },

        {keycode::colon , "(:)" },
        {keycode::equal , "(=)" },
        {keycode::comma , "(,)" },
        {keycode::minus , "(-)" },
        {keycode::period, "(.)" },
        {keycode::slash , "(/)" },
        {keycode::tilde , "(~)" },

        {keycode::bracket_left , "([)" },
        {keycode::backslash , "(\\)" },
        {keycode::bracket_right , "(])" },
        {keycode::quotation , "(')" },
    }};
    return map;
}
} // namespace ykm::input
