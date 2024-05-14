#ifndef YKM_TEST_HPP
#define YKM_TEST_HPP

#include <ostream>
#if __cplusplus < 202002L
#error "This code requires C++20 or later."
#endif

#include <cstddef>

#include <cstdint>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#define ytest_ostream_def ::std::ostream* __ytest_ostream
#define ytest_ostream_set_console __ytest_ostream = &::std::cout

#define ytest_ostream_def ::std::ostream* __ytest_ostream
#define ytest_ostream_cpy ::std::ostream* __ytest_ostream = ::__ytest_ostream
#define ytest_ostream_set_console __ytest_ostream = &::std::cout

#define ytest_ostream_file(name, code)                              \
    {                                                               \
        ytest_ostream_set_console;                                  \
        ::std::ofstream __output(name);                             \
        if (!__output.is_open())                                    \
        {                                                           \
            ytest_println("ytest>> err can't open file: {}", name); \
            return;                                                 \
        }                                                           \
        ytest_println("ytest>> print to file: {}", name);           \
        ytest_ostream_def = &__output;                              \
        code;                                                       \
        __output.close();                                           \
        ytest_ostream_set_console;                                  \
        ytest_println("ytest>> file close: {}", name);               \
    }

#define ytest_ostream_mem(reciver, code)  \
    {                                     \
        ::std::ostringstream __oss;       \
        ytest_ostream_def = &__oss;       \
        code;                             \
        reciver = std::move(__oss).str(); \
    }

#define ytest_ostream (*__ytest_ostream)

extern ytest_ostream_def = &std::cout;
/*
   format print
*/

inline static const char ytest_spaces[36] = "*.*.*. . . . . . . . . . . . . . . ";
#define ytest_indent(i) (&::ytest_spaces[sizeof(ytest_spaces) - 1 - (((i) & 0xF) << 1)])

#define ytest_println(...) ytest_ostream << ytest_indent(__indent) << ::std::format(__VA_ARGS__) << std::endl
#define ytest_print(...) ytest_ostream << ::std::format(__VA_ARGS__)

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
    ytest_run_test(Name##__ins, nullptr, argc, argv)

#define RunTestMul(Name, postfix)      \
    Name Name##postfix;                \
    Name##postfix.__indent = __indent; \
    ytest_run_test(Name##postfix, #postfix, argc, argv)

#define TestMain(e)                                             \
    int main(int argc, char** argv)                             \
    {                                                           \
        ytest_ostream_set_console;                              \
        ::std::cout << "\n----welcome!!!----\n" << ::std::endl; \
                                                                \
        ::ytest_bytesfmt = {4, 4};                              \
                                                                \
        TestBegin(0);                                           \
        e;                                                      \
        ::std::cout << "----all done----" << ::std::endl;       \
        return 0;                                               \
    }

#define TestMainFile(file, code)                                    \
    int main(int argc, char** argv)                                 \
    {                                                               \
        ::std::cout << "\n----welcome!!!----\n" << ::std::endl;     \
        ytest_ostream_set_console;                                  \
        ::ofstream __output(name);                                  \
        if (!__output.is_open())                                    \
        {                                                           \
            ytest_println("ytest>> err can't open file: {}", file); \
            return;                                                 \
        }                                                           \
        ytest_println("ytest>> print to file: {}", file);           \
        ytest_ostream_def = &__output;                              \
                                                                    \
        ::ytest_bytesfmt = {4, 4};                                  \
                                                                    \
        TestBegin(0);                                               \
        code;                                                       \
                                                                    \
        __output.close();                                           \
        ytest_ostream_set_console;                                  \
        ytest_println("ytest>> file close: {}", file);               \
        ytest_ostream_set_console;                                  \
        ::std::cout << "----all done----" << ::std::endl;           \
        return 0;                                                   \
    }

#define ytest_run_test(test, name, argc, argv)\
{\
    int __indent = test.__indent;\
    if (name)                                      \
        ytest_println("{}_{} {}", test.get_name(), name, "begin"); \
    else                                           \
        ytest_println("{} {}", test.get_name(), "begin");\
    ytest_println("~~ <$> ~~");\
\
    test.__indent++;\
    test.run(argc, argv);\
\
    ytest_println("~~ <&> ~~");\
\
    if (name)                                      \
        ytest_println("{}_{} {}\n", test.get_name(), name, "end"); \
    else                                           \
        ytest_println("{} {}\n", test.get_name(), "end");\
}\

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
   print binary
*/

struct ytest_bytes_fmt
{
    unsigned int unit = 4;
    unsigned int column = 4;
} __ytest_bytes_fmt;

#define ytest_bytesfmt __ytest_bytes_fmt
#define ytest_bytesfmt_def(v) ytest_bytes_fmt __ytest_bytes_fmt = v
#define ytest_bytesfmt_cpy(v) ytest_bytes_fmt __ytest_bytes_fmt = ::ytest_bytes_fmt
#define ytest_bytesfmt_reset(v) __ytest_bytes_fmt = ::ytest_bytes_fmt

inline void ytest_getbytes(::std::ostream& o, void* p, int size, ytest_bytes_fmt fmt, const char* indent)
{
    unsigned int s_unit = fmt.unit > 0 ? fmt.unit : 1;
    unsigned int s_line = fmt.column > 0 ? fmt.column : 1;

    unsigned int unit_fill=0, line_fill=0, offset = 0;
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

#define ytest_print_bytes(p, size)                       \
    ytest_println("bytes of {} , size: {}", #p, size); \
    ytest_getbytes(ytest_ostream, p, size, ytest_bytesfmt, ytest_indent(__indent + 1));\
    ytest_ostream << std::endl

#define ytest_print_bytes_d(p, size, des)            \
    ytest_println("size: {} des: {} ", size, des); \
    ytest_getbytes(ytest_ostream, p, size, ytest_bytesfmt, ytest_indent(__indent + 1));\
    ytest_ostream << std::endl

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
    [o] option print target | files | console | memory
    [ ] colorful output
*/

#endif
