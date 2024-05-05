/*
   user hardware interaction defs

version: dev 0.0.1
date : 2024/5/6

todo: joy controller
todo: touch pointers
todo: abstract interaction
*/
#ifndef YKM_INPUT_DEF_HPP
#define YKM_INPUT_DEF_HPP


#include <array>
#include <cstdint>
#include <cstring>
namespace ykm::input
{

enum state : uint8_t
{
    ks_up /*        */ = 0x1,
    ks_release /*   */ = 0x2,
    ks_up_mask /*   */ = ks_release & ks_up,

    ks_press /*     */ = 0x4,
    ks_down /*      */ = 0x8,
    ks_down_mask /* */ = ks_press & ks_down,
};

using state_bool = uint8_t;

using code_size = uint8_t;

template <typename Code, size_t Size>
struct state_machine
{
  public:
    void init(state s) { buffer.fill(state(s & (s << 4))); }

    state get_state(Code i) const
    {
        if (uint32_t(i) % 2 == 0)
            return state(buffer[uint32_t(i) / 2] >> 4);
        else
            return state(buffer[uint32_t(i) / 2] & 0x0f);
    }

    state_bool get_press(Code c) const { return get_state(c) & ks_press; }
    state_bool get_release(Code c) const { return get_state(c) & ks_release; }

    state_bool get(Code c) const { return get_state(c) & ks_down_mask; }

    state_bool get_down(Code c) const { return get_state(c) & ks_down; }
    state_bool get_up(Code c) const { return get_state(c) & ks_up; }

    uint8_t count_release() const { return size_r(); }
    uint8_t count_press() const { return size_p(); }

    Code peek_release(uint8_t i) const { return cache_release[i]; }
    Code peek_press(uint8_t i) const { return cache_press[i]; }

    void next_frame()
    {
        for (uint8_t i = 0; i <= size_r(); ++i)
            set_state(cache_release[i], ks_up);

        for (uint8_t i = 0; i <= size_p(); ++i)
            set_state(cache_press[i], ks_down);

        size_r() = 0;
        size_p() = 0;
    }

    void release(Code c)
    {
        if (get_state(c) & ks_up_mask)
        {
            set_state(c, ks_up);
            return;
        }
        set_state(c, ks_release);
        uint8_t index = (size_r()++) - 1;
        if (index < size)
            cache_release[index] = c;
    }

    void press(Code c)
    {
        if (get_state(c) & ks_down_mask)
        {
            set_state(c, ks_down);
            return;
        }

        set_state(c, ks_press);

        uint8_t index = (size_p()++) - 1;
        if (index < size)
            cache_press[index] = c;
    }

  protected:
    inline static constexpr uint8_t cache_size = Size / 2;
    inline static constexpr uint8_t size = cache_size - 1;

    std::array<state, cache_size> buffer; // 4bit
    std::array<Code, cache_size> cache_press;
    std::array<Code, cache_size> cache_release;

    void set_state(Code c, state s)
    {
        if (uint32_t(c) % 2 == 0)
            buffer[uint32_t(c) / 2] = state((buffer[uint32_t(c) / 2] & 0x0f) & (s << 4));
        else
            buffer[uint32_t(c) / 2] = state((buffer[uint32_t(c) / 2] & 0xf0) & s);
    }

    uint8_t size_r() const { return uint8_t(cache_release[size]); }
    uint8_t size_p() const { return uint8_t(cache_press[size]); }

    uint8_t& size_r() { return *((uint8_t*)&cache_release[size]); }
    uint8_t& size_p() { return *((uint8_t*)&cache_press[size]); }
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

struct mouse : state_machine<btncode, 16>
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

    left_shift /*   */ = 160,
    right_shift /*  */ = 161,
    left_ctrl /*    */ = 162,
    right_ctrl /*   */ = 163,
    left_alt /*     */ = 164,
    right_alt /*    */ = 165,

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

inline keycode kc_by_win(uint32_t kc) { return keycode(kc); }

using keyboard = state_machine<keycode, 256>;

// struct joy_controller
//{
//     int32_t id;
// };

} // namespace ykm::input

#endif
