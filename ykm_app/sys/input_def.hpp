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
#define YKM_APP_SYS_BTNCODE_ELEM\
    YKM_ENUM_EI_(invalid    , 0  )\
    YKM_ENUM_EI_(left       , 1  )\
    YKM_ENUM_EI_(right      , 2  )\
    YKM_ENUM_EI_(middle     , 3  )\
    YKM_ENUM_EI_(mouse1     , 1  )\
    YKM_ENUM_EI_(mouse2     , 2  )\
    YKM_ENUM_EI_(mouse3     , 3  )\
    YKM_ENUM_EI_(mouse4     , 4  )\
    YKM_ENUM_EI_(mouse5     , 5  )\
    YKM_ENUM_EI_(mouse6     , 6  )\
    YKM_ENUM_EI_(mouse7     , 7  )\
    YKM_ENUM_EI_(mouse8     , 8  )\
    YKM_ENUM_EI_(mouse9     , 9  )\
    YKM_ENUM_EI_(mouse10    , 10 )\
    YKM_ENUM_EI_(mouse11    , 11 )\
    YKM_ENUM_EI_(mouse12    , 12 )\
    YKM_ENUM_EI_(mouse13    , 13 )\
    YKM_ENUM_EI_(mouse14    , 14 )\
    YKM_ENUM_EI_(mouse15    , 15 )

// clang-format on

enum class btncode : uint8_t
{
    YKM_APP_SYS_BTNCODE_ELEM
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
#define YKM_APP_SYS_KEYCODE_ELEM \
YKM_ENUM_EI_(invalid                        , 0   )\
\
YKM_ENUM_EI_(backspace                      , 8   )\
YKM_ENUM_EI_(tab                            , 9   )\
\
YKM_ENUM_EI_(enter                          , 13  )\
YKM_ENUM_EI_(shift                          , 16  )\
YKM_ENUM_EI_(ctrl                           , 17  )\
YKM_ENUM_EI_(alt                            , 18  )\
YKM_ENUM_EI_(pausebreak                     , 19  )\
YKM_ENUM_EI_(capslock                       , 20  )\
\
YKM_ENUM_EI_(esc                            , 27  )\
\
YKM_ENUM_EI_(space                          , 32  )\
YKM_ENUM_EI_(pageup                         , 33  )\
YKM_ENUM_EI_(pagedown                       , 34  )\
YKM_ENUM_EI_(end                            , 35  )\
YKM_ENUM_EI_(home                           , 36  )\
YKM_ENUM_EI_(left                           , 37  )\
YKM_ENUM_EI_(up                             , 38  )\
YKM_ENUM_EI_(right                          , 39  )\
YKM_ENUM_EI_(down                           , 40  )\
\
YKM_ENUM_EI_(insert                         , 45  )\
YKM_ENUM_EI_(del                            , 46  )\
\
YKM_ENUM_ENI(_0         , "0"               , 48  )\
YKM_ENUM_ENI(_1         , "1"               , 49  )\
YKM_ENUM_ENI(_2         , "2"               , 50  )\
YKM_ENUM_ENI(_3         , "3"               , 51  )\
YKM_ENUM_ENI(_4         , "4"               , 52  )\
YKM_ENUM_ENI(_5         , "5"               , 53  )\
YKM_ENUM_ENI(_6         , "6"               , 54  )\
YKM_ENUM_ENI(_7         , "7"               , 55  )\
YKM_ENUM_ENI(_8         , "8"               , 56  )\
YKM_ENUM_ENI(_9         , "9"               , 57  )\
\
/* A-Z keycode.*/ \
YKM_ENUM_EI_(A                              , 65  )\
YKM_ENUM_EI_(B                              , 66  )\
YKM_ENUM_EI_(C                              , 67  )\
YKM_ENUM_EI_(D                              , 68  )\
YKM_ENUM_EI_(E                              , 69  )\
YKM_ENUM_EI_(H                              , 72  )\
YKM_ENUM_EI_(I                              , 73  )\
YKM_ENUM_EI_(J                              , 74  )\
YKM_ENUM_EI_(K                              , 75  )\
YKM_ENUM_EI_(L                              , 76  )\
YKM_ENUM_EI_(M                              , 77  )\
YKM_ENUM_EI_(N                              , 78  )\
YKM_ENUM_EI_(O                              , 79  )\
YKM_ENUM_EI_(P                              , 80  )\
YKM_ENUM_EI_(Q                              , 81  )\
YKM_ENUM_EI_(R                              , 82  )\
YKM_ENUM_EI_(S                              , 83  )\
YKM_ENUM_EI_(T                              , 84  )\
YKM_ENUM_EI_(U                              , 85  )\
YKM_ENUM_EI_(V                              , 86  )\
YKM_ENUM_EI_(W                              , 87  )\
YKM_ENUM_EI_(X                              , 88  )\
YKM_ENUM_EI_(Y                              , 89  )\
YKM_ENUM_EI_(Z                              , 90  )\
YKM_ENUM_EI_(super                          , 91  )/* win in windows, command in mac */\
\
YKM_ENUM_ENI(np_0       , "numpad(0)"       , 96  )\
YKM_ENUM_ENI(np_1       , "numpad(1)"       , 97  )\
YKM_ENUM_ENI(np_2       , "numpad(2)"       , 98  )\
YKM_ENUM_ENI(np_3       , "numpad(3)"       , 99  )\
YKM_ENUM_ENI(np_4       , "numpad(4)"       , 100 )\
YKM_ENUM_ENI(np_5       , "numpad(5)"       , 101 )\
YKM_ENUM_ENI(np_6       , "numpad(6)"       , 102 )\
YKM_ENUM_ENI(np_7       , "numpad(7)"       , 103 )\
YKM_ENUM_ENI(np_8       , "numpad(8)"       , 104 )\
YKM_ENUM_ENI(np_9       , "numpad(9)"       , 105 )\
YKM_ENUM_ENI(np_mul     , "numpad(*)"       , 106 )\
YKM_ENUM_ENI(np_plus    , "numpad(+)"       , 107 )\
YKM_ENUM_ENI(np_enter   , "numpad(enter)"   , 108 )\
YKM_ENUM_ENI(np_minus   , "numpad(-)"       , 109 )\
YKM_ENUM_ENI(np_dot     , "numpad(.)"       , 110 )\
YKM_ENUM_ENI(np_divide  , "numpad(/)"       , 111 )\
\
YKM_ENUM_EI_(F1                             , 112 )\
YKM_ENUM_EI_(F2                             , 113 )\
YKM_ENUM_EI_(F3                             , 114 )\
YKM_ENUM_EI_(F4                             , 115 )\
YKM_ENUM_EI_(F5                             , 116 )\
YKM_ENUM_EI_(F6                             , 117 )\
YKM_ENUM_EI_(F7                             , 118 )\
YKM_ENUM_EI_(F8                             , 119 )\
YKM_ENUM_EI_(F9                             , 120 )\
YKM_ENUM_EI_(F10                            , 121 )\
YKM_ENUM_EI_(F11                            , 122 )\
YKM_ENUM_EI_(F12                            , 123 )\
\
YKM_ENUM_ENI(l_shift     , "l-shift"        , 160 )\
YKM_ENUM_ENI(r_shift     , "r-shift"        , 161 )\
YKM_ENUM_ENI(l_ctrl      , "l-ctrl"         , 162 )\
YKM_ENUM_ENI(r_ctrl      , "r-ctrl"         , 163 )\
YKM_ENUM_ENI(l_alt       , "l-alt"          , 164 )\
YKM_ENUM_ENI(r_alt       , "r-alt"          , 165 )\
\
YKM_ENUM_ENI(colon       , "(:)"            , 186 )\
YKM_ENUM_ENI(equal       , "(=)"            , 187 )\
YKM_ENUM_ENI(comma       , "(,)"            , 188 )\
YKM_ENUM_ENI(minus       , "(-)"            , 189 )\
YKM_ENUM_ENI(period      , "(.)"            , 190 )\
YKM_ENUM_ENI(slash       , "(/)"            , 191 )\
YKM_ENUM_ENI(tilde       , "(~)"            , 192 )\
\
YKM_ENUM_ENI(bracket_left   ,"([)"          , 219 )\
YKM_ENUM_ENI(backslash      ,"(\\)"         , 220 )\
YKM_ENUM_ENI(bracket_right  ,"(])"          , 221 )\
YKM_ENUM_ENI(quotation      ,"(')"          , 222 )

// clang-format on
enum class keycode : uint8_t
{
    YKM_APP_SYS_KEYCODE_ELEM
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
