#ifndef YKM_TEST_H
#define YKM_TEST_H

#include <utility>
#include <vector>
#if __cplusplus < 202002L
#error "This code requires C++20 or later."
#endif

#include <chrono>
#include <cstddef>
#include <cstdint>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace ykm_test
{

struct bytes_fmt
{
    uint16_t unit = 4;
    uint16_t column = 4;
};

struct base
{
    using test_func = void (*)(base* self, int argc, char** argv);
    const char* test_name;
    test_func test_f;
    uint32_t ytest_indent;
    base(const char* test_name, test_func test_f);
};

void do_tests(uint32_t ytest_indent, ::std::vector<::ykm_test::base*> ytestqueue);

void getbytes(::std::ostream& o, void* p, int size, bytes_fmt fmt, const char* indent);

struct timer
{
    using time_t = ::std::chrono::time_point<::std::chrono::steady_clock>;
    using time_dt = ::std::chrono::duration<double>;
    static time_t now() { return ::std::chrono::high_resolution_clock::now(); }

    void clear_stored() { stored = time_dt(0); }
    void pause() { stored += now() - begin; };
    void start() { begin = now(); }

    std::string get_info();

    time_dt stored;
    time_t begin;
};

} // namespace ykm_test

extern ::std::ostream* ytest_out;
extern const char ytest_indent_str[36];
extern uint32_t ytest_indent;
extern uint32_t ytest_logwidth;
extern ::ykm_test::bytes_fmt ytest_bfmt;

extern ::std::vector<::ykm_test::base*> ytestqueue;

#define ytest_indent_get(i) &(ytest_indent_str[sizeof(ytest_indent_str) - 1 - (((i) & 0xF) << 1)])

#define ytest_endl ::ykm_test::endl

template <typename S, typename T, typename... Args>
inline void ykm_test_oss(S& s, T&& t, Args&&... args)
{
    s << std::forward<T>(t);
    if constexpr (sizeof...(args) > 0)
        ykm_test_oss(s, std::forward<Args>(args)...);
}

template <typename... Args>
inline std::string ykm_test_str(Args&&... args)
{
    std::ostringstream oss;
    ykm_test_oss(oss, std::forward<Args>(args)...);
    return std::move(oss).str();
}

#define _println(...) ykm_test_oss((*ytest_out), ytest_indent_get(ytest_indent), __VA_ARGS__, "\n")
#define _print(...) ykm_test_oss((*ytest_out), __VA_ARGS__)

#define ytest_indent_add(i, code) \
    {                             \
        ytest_indent += i;        \
        code;                     \
        ytest_indent -= i;        \
    }

#define ytest_call_queue

#define _ytest_ytest_global ::ykm_test::ctx
#define _ostream_set_console ytest_out = &::std::cout

#define begin_ostream_file(name)                               \
    {                                                          \
        auto __name = name;                                    \
        ::std::ofstream __output(name);                        \
        if (!__output.is_open())                               \
        {                                                      \
            _ostream_set_console;                              \
            _println("ytest>> err can't open file: ", __name); \
            return;                                            \
        }                                                      \
        _println("ytest>> print to file: ", __name);           \
        ytest_out = &__output;

#define end_ostream_file()                    \
    __output.close();                         \
    _ostream_set_console;                     \
    _println("ytest>> file close: ", __name); \
    }

#define _ostream_mem(reciver, code)       \
    {                                     \
        ::std::ostringstream __oss;       \
        _ostream_def = &__oss;            \
        code;                             \
        reciver = std::move(__oss).str(); \
    }

/*
   format print
*/

/*
   core
*/

#define Test(Name)                                                     \
    struct Name : ::ykm_test::base                                     \
    {                                                                  \
        void run(int argc, char** argv);                               \
        static void called(::ykm_test::base* p, int argc, char** argv) \
        {                                                              \
            ((Name*)p)->run(argc, argv);                               \
            return;                                                    \
        }                                                              \
        Name() : ::ykm_test::base(#Name, called) {}                    \
    } Name##_ins;                                                      \
    inline void Name::run(int argc, char** argv)

#define _print_argvs                                     \
    _println("argv num: ", argc, " \n<$>");              \
    for (int i = 0; i <= argc; i++)                      \
    {                                                    \
        _println(std::setw(4), i, " ~> {", argv[i], "}"); \
    }                                                    \
    _println("<end>\n");

/*
   feature print extensions
TODO:
[ ] example
*/

#define _logwidth_set(i) ytest_logwidth = i
#define _logwidth_def(i) uint32_t _logwidth_set(i)
#define _logwidth_reset _logwidth_set(::ytest_logwidth)
#define _logwidth_copy(i) uint32_t _logwidth_reset

#define _file_line __FILE__, ":",std::dec, __LINE__

// clang-format off

#define _assert_bool(Con) if (!Con) \
    { \
        _println(std::setw(ytest_logwidth), \
        ykm_test_str("assert_bool failed -> ", #Con),\
        " @", _file_line);                            \
        return; \
    } \

#define _assert_equal(A, B) if (A != B) \
    { \
        _println(std::setw(ytest_logwidth), \
        ykm_test_str("assert_equal  failed: ", #A, " != ", #B),\
        " @", _file_line); \
        return; \
    } \

#define _assert_not_equal(A, B) if (A == B) \
    { \
        _println(std::setw(ytest_logwidth), \
        ykm_test_str("assert_not_equal failed: ", #A, " == ", #B),\
        " @", _file_line); \
        return; \
    } \

#define _logexpr(expr) \
{\
        _println(std::setw(ytest_logwidth), \
        ykm_test_str(#expr, " => ", expr),\
        " @", _file_line); \
}

#define _logwrap(expr) expr; logexpr(expr)

// clang-format on

/*
   print binary
*/

#define _bytesfmt_dec ::ykm_test::bytes_fmt ytest_bfmt
#define _bytesfmt_def(v) ::ykm_test::bytes_fmt ytest_bfmt = v
#define _bytesfmt_cpy(v) ::ykm_test::bytes_fmt ytest_bfmt = ::ytest_bfmt
#define _bytesfmt_reset(v) ytest_bfmt = ::ytest_bfmt

#define _print_bytes(p, size)                                                                  \
    _println("bytes of ", #p, " size: ", size);                                                \
    ::ykm_test::getbytes(*ytest_out, p, size, ytest_bfmt, ytest_indent_get(ytest_indent + 1)); \
    *ytest_out << ::std::endl

#define _print_bytes_d(p, size, des)                                                           \
    _println("size: ", size, " des: ", des);                                                   \
    ::ykm_test::getbytes(*ytest_out, p, size, ytest_bfmt, ytest_indent_get(ytest_indent + 1)); \
    *ytest_out << ::std::endl

/*
   feature timer
TODO:
   [ ] example
*/

#define _time_reset              \
    __test_timer.clear_stored(); \
    __test_timer.start()
#define _time_start                 \
    ::ykm_test::timer __test_timer; \
    test_time_reset

#define _time_pause __test_timer.pause()

#define _time_continue __test_timer.start()
#define _time_peek __test_timer.get_info()

/*
    features TODO:
    [ ] wait thread quit
    [o] argv show
    [o] option print target | files | console | memory
    [ ] colorful output
*/

#endif
