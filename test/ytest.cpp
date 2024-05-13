#include <iostream>

#include <ykm/test.hpp>

Test(print_format)
{
    ::assert_width_set(32);
    {
        logexpr(64 + 99);

        assert_width(30);
        logexpr(4 % 5);

        assert_width_set(28);
        logexpr(4 / 5);

        assert_width_reset;
        logexpr(6 / 5);

        assert_width_set(32);
    }

    ytest_indent_add(1, {
        logexpr(1 + 1);
        assert_width_copy(1);
        logexpr(1 + 1);
    });
};

Test(T2)
{
    assert_bool(false);
    assert_width(32);
};

TestMain({
    RunTest(print_format);
    RunTest(T2);
})
