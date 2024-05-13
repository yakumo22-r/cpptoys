#ifndef YKM_TEST_HPP
#define YKM_TEST_HPP

#include <cstddef>
#include <vector>
#if __cplusplus < 202002L
#error "This code requires C++20 or later."
#endif

#include <cstdint>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>

/*
   format print
*/
inline static const char ytest_spaces[36] = "*.*.*. . . . . . . . . . . . . . . ";
#define ytest_indent(i) (&::ytest_spaces[sizeof(ytest_spaces) - 1 - ((i & 0xF) << 1)])

#define ytest_println(...) ::std::cout << ytest_indent(__indent) << ::std::format(__VA_ARGS__) << std::endl
#define ytest_print(...) ::std::cout << ytest_indent(__indent) << ::std::format(__VA_ARGS__)

#define ytest_indent_add(i, code) \
    {                             \
        __indent += i;            \
        code;                     \
        __indent -= i;            \
    }


/*
   core
*/
struct test_base
{
    virtual void run(int argc, char** argv) = 0;
    virtual const char* get_name() const = 0;
    int __indent = 0;
};

#define Test(Name)                                              \
    struct Name : test_base                                     \
    {                                                           \
      public:                                                   \
        void run(int argc, char** argv) override;               \
        const char* get_name() const override { return #Name; } \
    };                                                          \
    void Name::run(int argc, char** argv)

#define TestBegin(i) constexpr unsigned int __indent = i

#define RunTest(Name)                \
    Name Name##__ins;                \
    Name##__ins.__indent = __indent; \
    run_test(Name##__ins, nullptr, argc, argv);

#define RunTestMul(Name, postfix)      \
    Name Name##postfix;                \
    Name##postfix.__indent = __indent; \
    run_test(Name##postfix, #postfix, argc, argv);

#define TestMain(e)                 \
    int main(int argc, char** argv) \
    {                               \
        ::std::cout << "\n----welcome!!!----\n" << ::std::endl;\
        TestBegin(0);               \
        e;                          \
        ::std::cout << "----all done----" << ::std::endl;\
        return 0;                   \
    }

#define TEST_RUN_INFO(info, ty, name)              \
    if (name)                                      \
        ytest_println("{}_{} {}", ty, name, info); \
    else                                           \
        ytest_println("{} {}", ty, info);

inline void run_test(test_base& test, const char* name, int argc, char** argv)
{
    int __indent = test.__indent;
    TEST_RUN_INFO("begin", test.get_name(), name);

    test.__indent++;
    test.run(argc, argv);

    TEST_RUN_INFO("end", test.get_name(), name);
    ::std::cout << ::std::endl;
}

/*
   feature print extensions
TODO:
[ ] example
*/

#define assert_width_set(i) __ytest_assert_left = i
#define assert_width_def size_t __ytest_assert_left
#define assert_width(i) assert_width_def = i
#define assert_width_reset assert_width_set(::__ytest_assert_left)
#define assert_width_copy(i) assert_width_def = (::__ytest_assert_left + i)

extern assert_width(64);

inline std::string ytest_str_area(size_t size, const char* str)
{
    std::string o(str);
    o.resize(size, ' ');
    return o;
}

// clang-format off

#define assert_bool(Con) if (!Con) \
    { \
        auto __content = ytest_str_area(__ytest_assert_left, \
        ::std::format("assert_bool failed -> {}", #Con).c_str()); \
        ytest_println("{} @line {}", __content, __LINE__); \
        return; \
    } \

#define assert_equal(A, B) if (A != B) \
    { \
        auto __content = ytest_str_area(__ytest_assert_left, \
        ::std::format("assert_equal  failed: {} != {}   @line {}", #A, #B).c_str()); \
        ytest_println("{} @line {}", __content, __LINE__); \
        return; \
    } \

#define assert_not_equal(A, B) if (A == B) \
    { \
        auto __content = ytest_str_area(__ytest_assert_left, \
        ::std::format("assert_not_equal failed: {} != {}   @line {}", #A, #B).c_str()); \
        ytest_println("{} @line {}", __content, __LINE__); \
        return; \
    } \

#define logexpr(expr) \
{\
        auto __content = ytest_str_area(__ytest_assert_left, \
        ::std::format("{} => {}", #expr, expr).c_str()); \
        ytest_println("{} @line {}", __content, __LINE__);\
}

#define logwrap(expr) expr; logexpr(expr)

// clang-format on


/*
   feature print binary
TODO:
   [ ] example
*/
inline std::string ytest_getbytes(void* p, int size, int unit, int column, const char* indent)
{
    std::ostringstream oss;
    unsigned int s_unit = unit > 0 ? unit : 1;
    unsigned int s_line = column > 0 ? column : 1;

    unsigned int unit_fill, line_fill, offset = 0;
    unsigned char* buffer = (unsigned char*)p;
    while (offset < size)
    {
        if (unit_fill == 0 && line_fill == 0)
            ::std::cout << indent;

        ::std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(buffer[offset]);
        offset++;
        unit_fill++;
        if (unit_fill == s_unit)
        {
            ::std::cout << " ";
            line_fill++;
            if (line_fill == s_line)
            {
                ::std::cout << std::endl;
                line_fill = 0;
            }
            unit_fill = 0;
        }
    }
    return std::move(oss).str();
}

#define ytest_bytes(p, size, unit, col) ytest_println("bytes of {} , size: {}\n{}\n", #p, size, ytest_getbytes(p, size, unit, col, ytest_indent(__indent+1))

/*
   feature timer
TODO:
   [ ] example
*/
#include <chrono>

struct ytest_timer
{
    using time_t = ::std::chrono::time_point<::std::chrono::steady_clock>;
    using time_dt = ::std::chrono::duration<double>;
    static time_t now() { return ::std::chrono::high_resolution_clock::now(); }

    void clear_stored() { stored = time_dt(0); }
    void pause() { stored += now() - begin; };
    void start() { begin = now(); }

    std::string get_info()
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
    time_dt stored;
    time_t begin;
};

#define ytest_time_reset         \
    __test_timer.clear_stored(); \
    __test_timer.start()
#define ytest_time_start        \
    ::ytest_timer __test_timer; \
    test_time_reset

#define ytest_time_pause __test_timer.pause()

#define ytest_time_continue __test_timer.start()
#define ytest_time_peek __test_timer.get_info()


/*
    features TODO:
    [ ] wait thread quit
    [ ] argv show
    [ ] option print target | files | console | memory
*/

#endif
