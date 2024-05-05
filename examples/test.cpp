#include <format>
#include <iostream>
#include <typeinfo>
#include <any>
#include <ykm/place.hpp>

#define STATIC_STR(S) #S

constexpr unsigned int hash_constexpr(const char* str, int h = 0) { return !str[h] ? 5381 : (hash_constexpr(str, h + 1) * 33) ^ str[h]; }

struct A
{
};

namespace WE
{
struct A
{
};
} // namespace WE
enum E{

};

int main()
{
    std::any a;
    char asd[5] = "asd";
    std::cout << std::format("any size {}\n", sizeof(a));
    std::cout << std::format("enum is int:  {}\n", std::is_enum_v<E>);
    std::cout << std::format("enum class is int:  {}\n", std::is_enum_v<E>);
    std::cout << std::format("ykm::any size {}\n", sizeof(ykm::any));
    std::cout << std::format("hash 0 {}\n", typeid(A).hash_code());
    std::cout << std::format("hash 1 {}\n", typeid(WE::A).hash_code());
    return 0;
}
