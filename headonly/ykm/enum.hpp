#ifndef YKM_BITSET_H
#define YKM_BITSET_H

#include <array>
#include <bitset>
#include <cstddef>
#include <string_view>
#include <type_traits>
#include <unordered_map>

namespace ykm
{

template <typename E, size_t Size>
struct enum_set : std::bitset<Size>
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

template <typename E, size_t Size>
struct enum_map
{
    static_assert(std::is_enum_v<E> && std::is_unsigned_v<std::underlying_type_t<E>>, "type E must be unsigned enum (class)");
    using under_int = std::underlying_type_t<E>;

    inline static constexpr E null = E(~under_int(0));

    constexpr enum_map(const std::initializer_list<std::pair<E, const char*>>& list) : null_cstr("(null)")
    {
        v_str.fill(null_cstr);

        for (auto& e : list)
        {
            v_str[size_t(e.first)] = e.second;
            str_v.insert({std::string_view(e.second), e.first});
        }
    }

    E by_name(std::string_view str) const { return str_v[str]; }
    const char* by_code(E code) const { return v_str[size_t(code)]; }

    E operator[](std::string_view str) const { return by_name(str); }
    const char* operator[](E code) const { return by_code(code); }

    bool has(E code) const { return size_t(code) >= Size && v_str[size_t(code)] != null_cstr; }
    bool has(std::string_view str) const { return str_v.count(str); }

  private:
    const char* null_cstr;
    std::array<const char*, Size> v_str;
    std::unordered_map<std::string_view, E> str_v;
};

#define YKM_ENUM_E__(e) e,
#define YKM_ENUM_EN_(e, n) e,
#define YKM_ENUM_EI_(e, i) e = i,
#define YKM_ENUM_ENI(e, n, i) e = i,

} // namespace ykm

#endif
