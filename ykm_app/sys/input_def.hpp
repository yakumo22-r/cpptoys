/*
   user hardware interaction defs

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
#include <ykm/enum.hpp>

namespace ykm::input
{

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

    const buf_arr& buf_press() const { return buf_p; }
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

// clang-format off
#define YKM_APP_SYS_BTNCODE_ELEM(MACRO)\
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
    MACRO##_EI_(mouse14    , 14 )\
    MACRO##_EI_(mouse15    , 15 )\

// clang-format on

enum class btncode : uint8_t
{
    YKM_ENUM_DEFINE(YKM_APP_SYS_BTNCODE_ELEM) none,
};

extern const ykm::enum_map<btncode, 16> btncode_map;

struct mouse : istate<btncode, 16, 8>
{
  public:
    int32_t x() const { return _x; }
    int32_t& x() { return _x; }

    int32_t y() const { return _y; }
    int32_t& y() { return _y; }

    int32_t scroll() const { return _scroll; }
    int32_t& scroll() { return _scroll; }

  private:
    int32_t _scroll;
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

extern const ykm::enum_map<keycode, 256> keycode_map;

inline keycode kc_by_win(uint32_t kc) { return keycode(kc); }

using keyboard = istate<keycode, 256, 64>;

// struct joy_controller
//{
//     int32_t id;
// };

} // namespace ykm::input

#endif
