/*
   user hardware interaction def

version: dev 0.0.2
date : 2024/5/25

todo: joy controller
todo: touch pointers
todo: abstract interaction
*/
#ifndef YKM_APP_SYS_INPUT_DEF_HPP
#define YKM_APP_SYS_INPUT_DEF_HPP

#include <cstdint>
#include <cstring>

#include <array>

#include "../sys.h"
#include "../utils/enum.hpp"

namespace ykm::input
{

//***********************************//
//*********** base defs *************//

enum state : uint8_t
{
    ks_release /*   */ = 0x1,
    ks_up /*        */ = 0x2,
    ks_up_mask /*   */ = ks_release & ks_up,

    ks_down /*      */ = 0x4,
    ks_press /*     */ = 0x8,
    ks_down_mask /* */ = ks_press & ks_down,
};

using state_bool = uint8_t;

using code_size = uint8_t;

template <typename E, std::size_t S, std::size_t BufSize>
struct istate
{
  public:
    state get_state(E i) const { return ks_up << (curr[i] * 2) << prev[i]; }

    state_bool get_press(E c) const { return get_state(c) & ks_press; }
    state_bool get_release(E c) const { return get_state(c) & ks_release; }

    state_bool get(E c) const { return get_state(c) & ks_down_mask; }

    state_bool get_down(E c) const { return get_state(c) & ks_down; }
    state_bool get_up(E c) const { return get_state(c) & ks_up; }

    struct buf_arr;
    struct buf_itr_t final
    {
        // clang-format off
        operator E() { return *e; }
        buf_itr_t& operator++() { ++e; return *this; }
        buf_itr_t& operator--() { --e; return *this; }

        bool operator==(buf_itr_t r) const { return r.e == e; }
        bool operator!=(buf_itr_t r) const { return r.e != e; }
        E operator*() const { return *e; }

        buf_itr_t(const E* e) : e(e) {}

      private:
        friend buf_arr;
        const E* e;
        // clang-format on
    };

    struct buf_arr final
    {
        buf_arr() : size(0) {}
        void reset() { size = 0; }
        void push(E e) { buf[size++] = e; }
        bool is_full() const { return size == BufSize; }
        buf_itr_t begin() const { return buf_itr_t(buf.data()); }
        buf_itr_t end() const { return buf_itr_t(buf.data() + size); }

      private:
        uint32_t size;
        std::array<E, BufSize + 1> buf;
    };

    istate& press(E c)
    {
        if (!curr[c])
        {
            curr.set(c);
            buf_p.push(c);
        }
        return *this;
    }
    istate& release(E c)
    {
        if (curr[c])
        {
            curr.reset(c);
            buf_r.push(c);
        }
        return *this;
    }

    void next_frame()
    {
        buf_p.reset();
        buf_r.reset();
        prev = curr;
        curr.reset();
    };

    const buf_arr& buf_entered() const { return buf_p; }
    const buf_arr& buf_release() const { return buf_r; }

  private:
    ykm::enum_set<E, S> curr;
    ykm::enum_set<E, S> prev;

    buf_arr buf_p;
    buf_arr buf_r;
};

struct touch
{
    int32_t id;
    int32_t x;
    int32_t y;
    state s;
};

//*********** base defs *************//
//***********************************//

// clang-format off
#define YKM_APP_SYS_MOUSE_EVT_ELEM(MACRO)\
    MACRO##_EI_(left       , 1  )\
    MACRO##_EI_(right      , 2  )\
    MACRO##_EI_(middle     , 3  )\
    MACRO##_EI_(mouse1     , 1  )\
    MACRO##_EI_(mouse2     , 2  )\
    MACRO##_EI_(mouse3     , 3  )\
    MACRO##_EI_(mouse4     , 4  )\
    MACRO##_EI_(mouse5     , 5  )\
    MACRO##_EI_(mouse6     , 6  )\
    MACRO##_EI_(mouse7     , 7  )\
    MACRO##_EI_(mouse8     , 8  )\
    MACRO##_EI_(mouse9     , 9  )\
    MACRO##_EI_(mouse10    , 10 )\
    MACRO##_EI_(mouse11    , 11 )\
    MACRO##_EI_(mouse12    , 12 )\
    MACRO##_EI_(mouse13    , 13 )\
    MACRO##_EI_(scroll     , 14 )\
    MACRO##_EI_(move       , 15 )

// clang-format on

enum class mouse_evt : uint8_t
{
    YKM_ENUM_DEFINE(YKM_APP_SYS_MOUSE_EVT_ELEM) none,
};
YKM_SYS_API
extern const ykm::enum_map<mouse_evt, 16> mouseEvtMap;

struct mouse : istate<mouse_evt, 16, 8>
{
  public:
    int32_t x() const { return _x; }
    int32_t& x() { return _x; }

    int32_t y() const { return _y; }
    int32_t& y() { return _y; }

    void push_scroll_evt() { press(mouse_evt::scroll); }
    void push_move_evt() { press(mouse_evt::move); }

    int32_t scroll() const { return _scroll_y; }
    int32_t& scroll() { return _scroll_y; }

    int32_t scroll_x() const { return _scroll_x; }
    int32_t& scroll_x() { return _scroll_x; }

    int32_t scroll_y() const { return _scroll_y; }
    int32_t& scroll_y() { return _scroll_y; }

    void clear()
    {
        _scroll_x = 0;
        _scroll_y = 0;
        next_frame();
    }

  private:
    int32_t _scroll_x;
    int32_t _scroll_y;
    int32_t _x;
    int32_t _y;
};

// clang-format off
#define YKM_APP_SYS_KEYCODE_ELEM(MACRO) \
MACRO##_EI_(backspace                      , 8   )\
MACRO##_EI_(tab                            , 9   )\
\
MACRO##_EI_(enter                          , 13  )\
MACRO##_EI_(shift                          , 16  )\
MACRO##_EI_(ctrl                           , 17  )\
MACRO##_EI_(alt                            , 18  )\
MACRO##_EI_(pausebreak                     , 19  )\
MACRO##_EI_(capslock                       , 20  )\
\
MACRO##_EI_(esc                            , 27  )\
\
MACRO##_EI_(space                          , 32  )\
MACRO##_EI_(pageup                         , 33  )\
MACRO##_EI_(pagedown                       , 34  )\
MACRO##_EI_(end                            , 35  )\
MACRO##_EI_(home                           , 36  )\
MACRO##_EI_(left                           , 37  )\
MACRO##_EI_(up                             , 38  )\
MACRO##_EI_(right                          , 39  )\
MACRO##_EI_(down                           , 40  )\
\
MACRO##_EI_(insert                         , 45  )\
MACRO##_EI_(del                            , 46  )\
\
MACRO##_ENI(_0         , "0"               , 48  )\
MACRO##_ENI(_1         , "1"               , 49  )\
MACRO##_ENI(_2         , "2"               , 50  )\
MACRO##_ENI(_3         , "3"               , 51  )\
MACRO##_ENI(_4         , "4"               , 52  )\
MACRO##_ENI(_5         , "5"               , 53  )\
MACRO##_ENI(_6         , "6"               , 54  )\
MACRO##_ENI(_7         , "7"               , 55  )\
MACRO##_ENI(_8         , "8"               , 56  )\
MACRO##_ENI(_9         , "9"               , 57  )\
\
/* A-Z keycode.*/ \
MACRO##_EI_(A                              , 65  )\
MACRO##_EI_(B                              , 66  )\
MACRO##_EI_(C                              , 67  )\
MACRO##_EI_(D                              , 68  )\
MACRO##_EI_(E                              , 69  )\
MACRO##_EI_(F                              , 70  )\
MACRO##_EI_(G                              , 71  )\
MACRO##_EI_(H                              , 72  )\
MACRO##_EI_(I                              , 73  )\
MACRO##_EI_(J                              , 74  )\
MACRO##_EI_(K                              , 75  )\
MACRO##_EI_(L                              , 76  )\
MACRO##_EI_(M                              , 77  )\
MACRO##_EI_(N                              , 78  )\
MACRO##_EI_(O                              , 79  )\
MACRO##_EI_(P                              , 80  )\
MACRO##_EI_(Q                              , 81  )\
MACRO##_EI_(R                              , 82  )\
MACRO##_EI_(S                              , 83  )\
MACRO##_EI_(T                              , 84  )\
MACRO##_EI_(U                              , 85  )\
MACRO##_EI_(V                              , 86  )\
MACRO##_EI_(W                              , 87  )\
MACRO##_EI_(X                              , 88  )\
MACRO##_EI_(Y                              , 89  )\
MACRO##_EI_(Z                              , 90  )\
MACRO##_EI_(super                          , 91  )/* win in windows, command in mac */\
\
MACRO##_ENI(np_0       , "numpad(0)"       , 96  )\
MACRO##_ENI(np_1       , "numpad(1)"       , 97  )\
MACRO##_ENI(np_2       , "numpad(2)"       , 98  )\
MACRO##_ENI(np_3       , "numpad(3)"       , 99  )\
MACRO##_ENI(np_4       , "numpad(4)"       , 100 )\
MACRO##_ENI(np_5       , "numpad(5)"       , 101 )\
MACRO##_ENI(np_6       , "numpad(6)"       , 102 )\
MACRO##_ENI(np_7       , "numpad(7)"       , 103 )\
MACRO##_ENI(np_8       , "numpad(8)"       , 104 )\
MACRO##_ENI(np_9       , "numpad(9)"       , 105 )\
MACRO##_ENI(np_mul     , "numpad(*)"       , 106 )\
MACRO##_ENI(np_plus    , "numpad(+)"       , 107 )\
MACRO##_ENI(np_enter   , "numpad(enter)"   , 108 )\
MACRO##_ENI(np_minus   , "numpad(-)"       , 109 )\
MACRO##_ENI(np_dot     , "numpad(.)"       , 110 )\
MACRO##_ENI(np_divide  , "numpad(/)"       , 111 )\
\
MACRO##_EI_(F1                             , 112 )\
MACRO##_EI_(F2                             , 113 )\
MACRO##_EI_(F3                             , 114 )\
MACRO##_EI_(F4                             , 115 )\
MACRO##_EI_(F5                             , 116 )\
MACRO##_EI_(F6                             , 117 )\
MACRO##_EI_(F7                             , 118 )\
MACRO##_EI_(F8                             , 119 )\
MACRO##_EI_(F9                             , 120 )\
MACRO##_EI_(F10                            , 121 )\
MACRO##_EI_(F11                            , 122 )\
MACRO##_EI_(F12                            , 123 )\
\
MACRO##_ENI(l_shift     , "l-shift"        , 160 )\
MACRO##_ENI(r_shift     , "r-shift"        , 161 )\
MACRO##_ENI(l_ctrl      , "l-ctrl"         , 162 )\
MACRO##_ENI(r_ctrl      , "r-ctrl"         , 163 )\
MACRO##_ENI(l_alt       , "l-alt"          , 164 )\
MACRO##_ENI(r_alt       , "r-alt"          , 165 )\
\
MACRO##_ENI(colon       , "(:)"            , 186 )\
MACRO##_ENI(equal       , "(=)"            , 187 )\
MACRO##_ENI(comma       , "(,)"            , 188 )\
MACRO##_ENI(minus       , "(-)"            , 189 )\
MACRO##_ENI(period      , "(.)"            , 190 )\
MACRO##_ENI(slash       , "(/)"            , 191 )\
MACRO##_ENI(tilde       , "(~)"            , 192 )\
\
MACRO##_ENI(bracket_left   ,"([)"          , 219 )\
MACRO##_ENI(backslash      ,"(\\)"         , 220 )\
MACRO##_ENI(bracket_right  ,"(])"          , 221 )\
MACRO##_ENI(quotation      ,"(')"          , 222 )

// clang-format on
enum class keycode : uint8_t
{
    YKM_ENUM_DEFINE(YKM_APP_SYS_KEYCODE_ELEM) none,
};

YKM_SYS_API
extern const ykm::enum_map<keycode, 256> keyCodeMap;

inline keycode kc_by_sc(int scancode)
{
#if defined(_WIN32)
    return keycode(scancode);
#elif defined(__APPLE__)
    static const keycode maps[0x80] = {
        keycode::A,             // 0
        keycode::S,             // 1
        keycode::D,             // 2
        keycode::F,             // 3
        keycode::H,             // 4
        keycode::G,             // 5
        keycode::Z,             // 6
        keycode::X,             // 7
        keycode::C,             // 8
        keycode::V,             // 9
        keycode::none,          // 10
        keycode::B,             // 11
        keycode::Q,             // 12
        keycode::W,             // 13
        keycode::E,             // 14
        keycode::R,             // 15
        keycode::Y,             // 16
        keycode::T,             // 17
        keycode::_1,            // 18
        keycode::_2,            // 19
        keycode::_3,            // 20
        keycode::_4,            // 21
        keycode::_6,            // 22
        keycode::_5,            // 23
        keycode::equal,         // 24
        keycode::_9,            // 25
        keycode::_7,            // 26
        keycode::minus,         // 27
        keycode::_8,            // 28
        keycode::_0,            // 29
        keycode::bracket_right, // 30
        keycode::O,             // 31
        keycode::U,             // 32
        keycode::bracket_left,  // 33
        keycode::I,             // 34
        keycode::P,             // 35
        keycode::enter,         // 36
        keycode::L,             // 37
        keycode::J,             // 38
        keycode::quotation,     // 39
        keycode::K,             // 40
        keycode::colon,         // 41
        keycode::backslash,     // 42
        keycode::comma,         // 43
        keycode::slash,         // 44
        keycode::N,             // 45
        keycode::M,             // 46
        keycode::period,        // 47
        keycode::tab,           // 48
        keycode::space,         // 49
        keycode::tilde,         // 50
        keycode::backspace,     // 51
        keycode::none,          // 52
        keycode::esc,           // 53
        keycode::none,          // 54
        keycode::super,         // 55
        keycode::l_shift,       // 56
        keycode::capslock,      // 57
        keycode::l_alt,         // 58
        keycode::l_ctrl,        // 59
        keycode::r_shift,       // 60
        keycode::r_alt,         // 61
        keycode::r_ctrl,        // 62
        keycode::none,          // 63
        keycode::none,          // 64
        keycode::np_dot,        // 65
        keycode::none,          // 66
        keycode::np_mul,        // 67
        keycode::none,          // 68
        keycode::np_plus,       // 69
        keycode::none,          // 70
        keycode::none,          // 71
        keycode::none,          // 72
        keycode::none,          // 73
        keycode::none,          // 74
        keycode::np_divide,     // 75
        keycode::np_enter,      // 76
        keycode::none,          // 77
        keycode::np_minus,      // 78
        keycode::none,          // 79
        keycode::none,          // 80
        keycode::none,          // 81
        keycode::np_0,          // 82
        keycode::np_1,          // 83
        keycode::np_2,          // 84
        keycode::np_3,          // 85
        keycode::np_4,          // 86
        keycode::np_5,          // 87
        keycode::np_6,          // 88
        keycode::np_7,          // 89
        keycode::none,          // 80
        keycode::np_8,          // 91
        keycode::np_9,          // 92
        keycode::none,          // 93
        keycode::none,          // 94
        keycode::none,          // 95
        keycode::F5,            // 96
        keycode::F6,            // 97
        keycode::F7,            // 98
        keycode::F3,            // 99
        keycode::F8,            // 100
        keycode::F9,            // 101
        keycode::none,          // 102
        keycode::F11,           // 103
        keycode::none,          // 104
        keycode::none,          // 105
        keycode::none,          // 106
        keycode::none,          // 107
        keycode::none,          // 108
        keycode::F10,           // 109
        keycode::none,          // 110
        keycode::F12,           // 111
        keycode::none,          // 112
        keycode::none,          // 113
        keycode::none,          // 114
        keycode::home,          // 115
        keycode::pageup,        // 116
        keycode::none,          // 117
        keycode::F4,            // 118
        keycode::end,           // 119
        keycode::F2,            // 120
        keycode::pagedown,      // 121
        keycode::F1,            // 122
        keycode::left,          // 123
        keycode::right,         // 124
        keycode::down,          // 125
        keycode::up,            // 126
        keycode::none,          // 127
    };
    return maps[scancode & 0x7F];
#endif
}

using keyboard = istate<keycode, 256, 64>;

// struct joy_controller
//{
//     int32_t id;
// };

} // namespace ykm::input

#endif
