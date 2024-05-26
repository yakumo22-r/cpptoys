#include <ykm/test_src.hpp>

Test(print_format)
{
    _logwidth_def(32);
    {
        _logexpr(64 + 99);

        _logwidth_set(30);
        _logexpr(4 % 5);

        _logwidth_set(28);
        _logexpr(4 / 5);

        _logwidth_reset;
        _logexpr(6 / 5);

        _logwidth_set(32);
    }

    ytest_indent_add(1, {
        _logexpr(1 + 1);
        _logwidth_set(1);
        _logexpr(1 + 1);
    });
};

Test(print_to_file)
{
    begin_ostream_file("print_to_file.log");

    _logexpr(4 % 4);
    _logexpr(4 % 5);
    _logexpr(4 % 6);
    _logexpr(4 % 7);
    _logexpr(4 % 8);

    end_ostream_file();
};

Test(print_bytes)
{
    int o = 1;
    _print_bytes_d(&o, sizeof(o), "+1");

    o = -1;
    _print_bytes_d(&o, sizeof(o), "-1");
};

#include <ykm/enum.h>

enum class EC : unsigned
{
    A,
    B,
    C,
};
struct SE
{
    enum E : unsigned
    {
        A,
        B,
        C,
    };
};
Test(enum_set)
{
    ykm::enum_set<EC, 32> ec;
    ykm::enum_set<SE::E, 32> se;
    std::bitset<sizeof(EC)> ecs;

    int a = ec[EC::A];

    ec.set(EC::B);
    _println("A: {} B: {}", ec.test(EC::A), ec.test(EC::B));
    ec.set(EC::A).reset(EC::B);

    _println("after A: {} B: {}", ec.test(EC::A), ec.test(EC::B));

    ykm::enum_map<EC, 4> map = {{
        {EC::A, "A"},
        {EC::B, "B"},
        {EC::C, "C"},
    }};

    _logexpr(map.by_code(EC::A));
    _logexpr(map.by_code(EC::B));
};
