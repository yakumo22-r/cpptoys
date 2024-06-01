#ifndef YKM_ENUM_HPP
#define YKM_ENUM_HPP

#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace ykm
{

template <typename E, size_t Size> struct enum_set : std::bitset<Size>
{
  public:
    static_assert(std::is_enum_v<E> && std::is_unsigned_v<std::underlying_type_t<E>>, "type E must be unsigned enum (class)");
    using under_int = std::underlying_type_t<E>;

    bool operator[](E e) { return bitset().test(size_t(e)); }
    bool operator[](E e) const { return bitset().test(size_t(e)); }

    enum_set() : std::bitset<Size>() {}

    enum_set& set(E e)
    {
        bitset().set(size_t(e));
        return *this;
    }

    enum_set& set(size_t e)
    {
        bitset().set(e);
        return *this;
    }

    enum_set& reset(E e)
    {
        bitset().reset(size_t(e));
        return *this;
    }

    enum_set& reset()
    {
        bitset().reset();
        return *this;
    }

    bool test(E e) { return bitset().test(size_t(e)); }

    enum_set& flip(E e)
    {
        bitset().flip(size_t(e));
        return *this;
    }

  private:
    std::bitset<Size>& bitset() { return *this; }
    const std::bitset<Size>& bitset() const { return *this; }
};

template <uint64_t Seed> inline constexpr uint64_t enum_name_chash(const char* str)
{
    uint64_t code = Seed;
    while (*str) code = code * Seed + *str++;
    return code;
}

template <uint64_t Seed> uint64_t enum_name_hash(std::string_view strv)
{
    uint64_t code = Seed;
    const char* str = strv.data();
    while (*str) code = code * Seed + *str++;
    return code;
}

using enum_name_hasher = uint64_t (*)(std::string_view);

template <typename E> using enum_mapper = E (*)(uint64_t);

#define YKM_ENUM_MAP_HASHER(SEED)                     \
    [](std::string_view strv)                         \
    {                                                 \
        uint64_t code = SEED;                         \
        const char* str = strv.data();                \
        while (*str) { code = code * SEED + *str++; } \
        return code;                                  \
    }

template <typename E, size_t Size> struct enum_map
{
    static_assert(std::is_enum_v<E> && std::is_unsigned_v<std::underlying_type_t<E>>, "type E must be unsigned enum (class)");
    using under_int = std::underlying_type_t<E>;

    using mapper = ykm::enum_mapper<E>;
    using hasher = ykm::enum_name_hasher;

    constexpr enum_map(const std::initializer_list<std::pair<E, const char*>>& list, mapper str_v, hasher f)
        : null_cstr("(null)"), e_list(), e_size(0), v_str(), str_v(str_v), _f(f)
    {
        v_str.fill(null_cstr);

        uint32_t i = 0;
        for (auto& e : list)
        {
            v_str[size_t(e.first)] = e.second;
            e_list[i] = e.first;
            i++;
        }
        e_size = i;
    }

    E by_name(std::string_view str) const { return str_v(_f(str)); }
    const char* by_code(E code) const { return v_str[size_t(code)]; }

    E operator[](std::string_view str) const { return by_name(str); }
    const char* operator[](E code) const { return by_code(code); }

    bool has(E code) const { return size_t(code) >= Size && v_str[size_t(code)] != null_cstr; }
    bool has(std::string_view str) const { return str_v(_f(str)); }

    const E* begin() const { return e_list.begin(); };
    const E* end() const { return e_list.begin() + e_size; }

  private:
    const char* null_cstr;
    std::array<E, Size + 1> e_list;
    uint32_t e_size;
    std::array<const char*, Size + 1> v_str;
    mapper str_v;
    hasher _f;
};

#define YKM_ENUM_MAP(E, END) ykm::enum_map<E, size_t(E::END) + 1>

#define YKM_ENUM_E__(e) e,
#define YKM_ENUM_EN_(e, n) e,
#define YKM_ENUM_EI_(e, i) e = i,
#define YKM_ENUM_ENI(e, n, i) e = i,

#define YKM_ENUM_DEFINE(MACRO) MACRO(YKM_ENUM)

// clang-format off
#define YKM_ENUM_MAP_NS define_this_macro_when_see_error

#define YKM_ENUM_MAP_E__(e)         {YKM_ENUM_MAP_NS::e, #e},
#define YKM_ENUM_MAP_EN_(e, n)      {YKM_ENUM_MAP_NS::e, n},
#define YKM_ENUM_MAP_EI_(e, i)      {YKM_ENUM_MAP_NS::e, #e},
#define YKM_ENUM_MAP_ENI(e, n, i)   {YKM_ENUM_MAP_NS::e, n},

#define YKM_ENUM_KM_E__(e)          case ykm::enum_name_chash<YKM_ENUM_HASHSEED>(#e): return YKM_ENUM_MAP_NS::e;
#define YKM_ENUM_KM_EN_(e, n)       case ykm::enum_name_chash<YKM_ENUM_HASHSEED>(n):  return YKM_ENUM_MAP_NS::e;
#define YKM_ENUM_KM_EI_(e, i)       case ykm::enum_name_chash<YKM_ENUM_HASHSEED>(#e): return YKM_ENUM_MAP_NS::e;
#define YKM_ENUM_KM_ENI(e, n, i)    case ykm::enum_name_chash<YKM_ENUM_HASHSEED>(n):  return YKM_ENUM_MAP_NS::e;

#define YKM_ENUM_KMFUNC(MACRO,Default) \
    [](uint64_t code)->YKM_ENUM_MAP_NS {\
        switch(code){ MACRO(YKM_ENUM_KM) }\
        return YKM_ENUM_MAP_NS::Default;\
    }\

#define YKM_ENUM_HASHSEED 7575
#define YKM_ENUM_MAP_BUILD(MACRO,Default)\
    {MACRO(YKM_ENUM_MAP)},\
    YKM_ENUM_KMFUNC(MACRO,Default),\
    ykm::enum_name_hash<YKM_ENUM_HASHSEED>\


} // namespace ykm

#endif
