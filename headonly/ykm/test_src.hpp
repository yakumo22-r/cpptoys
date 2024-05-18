#include "test.h"

namespace ykm_test
{

::std::vector<::ykm_test::base*> ytestqueue;

inline base::base(const char* n, test_func f) : test_name(n), test_f(f) { ytestqueue.push_back(this); }

void getbytes(::std::ostream& o, void* p, int size, bytes_fmt fmt, const char* indent)
{
    uint16_t s_unit = fmt.unit > 0 ? fmt.unit : 1;
    uint16_t s_line = fmt.column > 0 ? fmt.column : 1;

    uint16_t unit_fill = 0, line_fill = 0, offset = 0;
    unsigned char* buffer = (unsigned char*)p;
    while (offset < size)
    {
        if (!(unit_fill | line_fill))
            o << indent;

        o << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(buffer[offset]);
        offset++;
        unit_fill++;
        if (unit_fill == s_unit)
        {
            o << " ";
            line_fill++;
            if (line_fill == s_line)
            {
                o << std::endl;
                line_fill = 0;
            }
            unit_fill = 0;
        }
    }
}

std::string timer::get_info()
{
    using namespace std::chrono;
    auto nano = duration_cast<nanoseconds>(stored).count();
    if (nano < 100)
        return std::format("{}nano", nano);

    auto micro = duration_cast<microseconds>(stored).count();
    if (micro < 100)
        return std::format("{}micro", micro);

    auto ms = duration_cast<milliseconds>(stored).count();
    if (ms < 10000)
        return std::format("{}ms", ms);

    uint32_t s = ms % 1000;
    if (s < 60)
        return std::format("{} s", s);

    uint32_t M = s % 60;
    if (M < 60)
        return std::format("{}M {}s {}ms", M, s % 60, ms % 1000);

    uint32_t H = M % 60;
    return std::format("{}H {}M {}s {}ms", H, M % 60, s % 60, ms % 1000);
}

std::string str_area(size_t size, const char* str)
{
    std::string o(str);
    o.resize(size, ' ');
    return o;
}

void do_tests(uint32_t ytest_indent, ::std::vector<::ykm_test::base*> ytestqueue, int argc, char** argv)
{
    for (auto p : ytestqueue)
    {
        _println("{} {}", p->test_name, "begin");

        _println("~~ <$>");

        p->ytest_indent = ytest_indent + 1;
        p->test_f(p, argc, argv);

        _println("~~ <&>");

        _println("{} {}\n", p->test_name, "end");
    }
}

} // namespace ykm_test

::std::ostream* ytest_out = &::std::cout;
const char ytest_indent_str[36] = "*.*.*. . . . . . . . . . . . . . . ";
uint32_t ytest_indent = 0;
uint32_t ytest_logwidth = 0;
::ykm_test::bytes_fmt ytest_bfmt = {4, 4};

int main(int argc, char** argv)
{
    ::std::cout << "\n----welcome!!!----\n" << ::std::endl;

    ::ykm_test::do_tests(0, ::ykm_test::ytestqueue, argc, argv);

    ::std::cout << "----all done----" << ::std::endl;
    return 0;
}
