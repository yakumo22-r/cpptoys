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
#include <ykm/enum.h>

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

enum class btncode : uint8_t
{
    invalid /*      */ = 0,
    left /*         */ = 1,
    right /*        */ = 2,
    middle /*       */ = 3,
    M1 /*           */ = 1,
    M2 /*           */ = 2,
    M3 /*           */ = 3,

    M4 /*           */ = 4,
    M5 /*           */ = 5,
    M6 /*           */ = 6,
    M7 /*           */ = 7,
    M8 /*           */ = 8,
    M9 /*           */ = 9,
    M10 /*          */ = 10,
    M11 /*          */ = 11,
    M12 /*          */ = 12,
    M13 /*          */ = 13,
    M14 /*          */ = 14,
    M15 /*          */ = 15,
};
const ykm::enum_map<btncode, 16>& btncode_map();

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

enum class keycode : uint8_t
{
    invalid /*      */ = 0,

    backspace /*    */ = 8,
    tab /*          */ = 9,

    enter /*        */ = 13,
    shift /*        */ = 16,
    ctrl /*         */ = 17,
    alt /*          */ = 18,
    pausebreak /*   */ = 19,
    capslock /*     */ = 20,

    esc /*          */ = 27,

    space /*        */ = 32,
    pageup /*       */ = 33,
    pagedown /*     */ = 34,
    end /*          */ = 35,
    home /*         */ = 36,
    left /*         */ = 37,
    up /*           */ = 38,
    right /*        */ = 39,
    down /*         */ = 40,

    insert /*       */ = 45,
    del /*          */ = 46,

    _0 /*           */ = 48,
    _1 /*           */ = 49,
    _2 /*           */ = 50,
    _3 /*           */ = 51,
    _4 /*           */ = 52,
    _5 /*           */ = 53,
    _6 /*           */ = 54,
    _7 /*           */ = 55,
    _8 /*           */ = 56,
    _9 /*           */ = 57,

    // A-Z keycode.
    A /*            */ = 65,
    B /*            */ = 66,
    C /*            */ = 67,
    D /*            */ = 68,
    E /*            */ = 69,
    H /*            */ = 72,
    I /*            */ = 73,
    J /*            */ = 74,
    K /*            */ = 75,
    L /*            */ = 76,
    M /*            */ = 77,
    N /*            */ = 78,
    O /*            */ = 79,
    P /*            */ = 80,
    Q /*            */ = 81,
    R /*            */ = 82,
    S /*            */ = 83,
    T /*            */ = 84,
    U /*            */ = 85,
    V /*            */ = 86,
    W /*            */ = 87,
    X /*            */ = 88,
    Y /*            */ = 89,
    Z /*            */ = 90,
    super /*        */ = 91, // win in windows, command in mac

    np_0 /*         */ = 96,
    np_1 /*         */ = 97,
    np_2 /*         */ = 98,
    np_3 /*         */ = 99,
    np_4 /*         */ = 100,
    np_5 /*         */ = 101,
    np_6 /*         */ = 102,
    np_7 /*         */ = 103,
    np_8 /*         */ = 104,
    np_9 /*         */ = 105,
    np_mul /*       */ = 106, // * key
    np_plus /*      */ = 107, // + key
    np_enter /*     */ = 108,
    np_minus /*     */ = 109, // - key
    np_dot /*       */ = 110, // . key
    np_divide /*    */ = 111, // / key
    F1 /*           */ = 112,
    F2 /*           */ = 113,
    F3 /*           */ = 114,
    F4 /*           */ = 115,
    F5 /*           */ = 116,
    F6 /*           */ = 117,
    F7 /*           */ = 118,
    F8 /*           */ = 119,
    F9 /*           */ = 120,
    F10 /*          */ = 121,
    F11 /*          */ = 122,
    F12 /*          */ = 123,

    l_shift /*  */ = 160,
    r_shift /*  */ = 161,
    l_ctrl /*   */ = 162,
    r_ctrl /*   */ = 163,
    l_alt /*    */ = 164,
    r_alt /*    */ = 165,

    colon /*        */ = 186, // :;
    equal /*        */ = 187, // +=
    comma /*        */ = 188, // <,
    minus /*        */ = 189, // _-
    period /*       */ = 190, // >.
    slash /*        */ = 191, // ?/
    tilde /*        */ = 192, // ~

    bracket_left /* */ = 219, // {[
    backslash /*    */ = 220, /* |\ */
    bracket_right /**/ = 221, // }]
    quotation /*    */ = 222, // "'
};
const ykm::enum_map<keycode, 256>& keycode_map();

inline keycode kc_by_win(uint32_t kc) { return keycode(kc); }

using keyboard = istate<keycode, 256, 64>;

// struct joy_controller
//{
//     int32_t id;
// };

} // namespace ykm::input

#endif
