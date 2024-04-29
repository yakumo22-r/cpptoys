#include <cstdint>
#include <cstring>
#include <format>
#include <iomanip>
#include <iostream>
#include <memory>

#include "ykm/serpack.hpp"

struct A
{
    int a;
    int b;
    char c;
    const char* str;
};

template <>
ykm::serpack ykm_serpack_tbl<A>(const A& a)
{
    ykm::serpack packer;
    return packer.push(a.a, a.b, a.c, ykm::packcstr(a.str));
}

template <>
A ykm_unpack_tbl<A>(ykm::serpack& pack)
{
    A a;
    ykm::packcstr str;
    pack.get_ref(a.a, a.b, a.c, str);
    a.str = str.str;
    return a;
}

void print_bytes(void* p, int size, int unit, int column)
{
    int s_unit = unit > 0 ? unit : 1;
    int s_line = column > 0 ? column : 1;

    int unit_fill = 0;
    int line_fill = 0;
    int offset = 0;
    unsigned char* buffer = (unsigned char*)p;
    while (offset < size)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(buffer[offset]);
        offset++;
        unit_fill++;
        if (unit_fill == s_unit)
        {
            std::cout << " ";
            line_fill++;
            if (line_fill == s_line)
            {
                std::cout << std::endl;
                line_fill = 0;
            }
            unit_fill = 0;
        }
    }

    std::cout << " end" << std::endl;
}

struct mem{
    int a = 0;
    char b = 1;
    int c = 2;
};

int main()
{
     //ykm::serpack packer;
     //A a;
     //a.a = 1;
     //a.b = 2;
     //a.c = 'c';
     //a.str = "wcnm";

    int64_t a = 100;

    char b[sizeof(int64_t)];

    char c[sizeof(int64_t)];

    memcpy(b, &a, sizeof(int64_t));
    (*(int64_t*)c) = a;
    print_bytes(&a, sizeof(int64_t), 8, 4);
    print_bytes(&b, sizeof(int64_t), 8, 4);
    print_bytes(&c, sizeof(int64_t), 8, 4);

    mem m;
    m.a = 0xaa;
    m.b = 255;
    m.c = 0x66006600;
    print_bytes(&m, sizeof(mem), 1, 4);
    void* p = (void*)int(0x66ccff);
    print_bytes(&p, sizeof(void*), 1, 4);
    


    std::cout << "mem " << alignof(mem) << std::endl;
    std::cout << "int " << alignof(int) << std::endl;
    std::cout << "char " << alignof(char) << std::endl;
    // std::cout << std::format("a: {}, b: {}, c: {}", a.a, a.b, a.c);
    //try
    //{
    //    packer = ykm_serpack_tbl(a);
    //    std::cout << "1" << std::endl;

    //    A b = ykm_unpack_tbl<A>(packer);
    //    std::cout << "2" << std::endl;
    //    std::cout << std::format("a: {}, b: {}, c: {}, str: {}", b.a, b.b, b.c, b.str);
    //}
    //catch (std::exception e)
    //{
    //    std::cout << e.what();
    //}

    return 0;
}
