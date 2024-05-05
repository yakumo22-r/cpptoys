/*
codev && string

last date:  2024/5/04
version:    dev 0.0.2
*/
#ifndef YKM_STRING_HPP
#define YKM_STRING_HPP
#include <string>

#ifdef _WIN32
#include <Windows.h>
namespace ykm
{

enum class code_page : uint16_t
{
    ansi = CP_ACP,
    utf8 = CP_UTF8,
};

inline std::string string_convert(const char* str, code_page in, code_page out)
{
    static LPWSTR wb = nullptr;
    static size_t wb_s = 0;
    int wb_need = MultiByteToWideChar(UINT(in), 0, str, -1, NULL, 0);
    if (wb_need > wb_s)
    {
        if (wb)
            delete[] wb;
        wb = new WCHAR[wb_need];
        wb_s = wb_need;
    }
    MultiByteToWideChar(UINT(in), 0, str, -1, wb, wb_need);

    static char* ob = nullptr;
    static size_t ob_s = 0;
    int ob_need = WideCharToMultiByte(UINT(in), 0, wb, -1, NULL, 0, NULL, NULL);
    if (ob_need > ob_s)
    {
        if (ob)
            delete[] ob;
        ob = new char[ob_need];
        ob_s = ob_need;
    }
    WideCharToMultiByte(UINT(out), 0, wb, -1, ob, ob_need, NULL, NULL);

    return std::string(ob);
}
} // namespace ykm

#endif

#endif
