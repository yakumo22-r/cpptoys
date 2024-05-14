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

Test(print_to_file){ytest_ostream_file("print_to_file.log", {
    logexpr(4 % 4);
    logexpr(4 % 5);
    logexpr(4 % 6);
    logexpr(4 % 7);
    logexpr(4 % 8);
})};

Test(print_bytes)
{
    int o = 1;
    ytest_print_bytes_d(&o, sizeof(o), "+1");

    o = -1;
    ytest_print_bytes_d(&o, sizeof(o), "-1");
};

TestMain({
    RunTest(print_format);
    RunTest(print_to_file);
    RunTest(print_bytes);
})
