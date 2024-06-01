#include <cstddef>
#include <iostream>
#include <ykm/enum.hpp>

// clang-format off
#define MyEnum_ELEMS(MACRO)                     \
    MACRO##_E__(A)                               \
    MACRO##_EN_(B,"love")                               \
    MACRO##_E__(C)                               \
    MACRO##_E__(D)
// clang-format on

enum class MyEnum : unsigned int
{
    YKM_ENUM_DEFINE(MyEnum_ELEMS) Size,
    None,
};

#undef YKM_ENUM_MAP_NS
#define YKM_ENUM_MAP_NS MyEnum
YKM_ENUM_MAP(MyEnum, None) map(YKM_ENUM_MAP_BUILD(MyEnum_ELEMS, None));

int main()
{
    std::cout << map.by_code(MyEnum::Size) << std::endl;
    std::cout << map.by_code(MyEnum::None) << std::endl;
    std::cout << map.by_code(map.by_name("A")) << std::endl;
    std::cout << map[MyEnum::B] << std::endl;
    std::cout << (map["C"] == MyEnum::C) << std::endl;
    return 0;
}
