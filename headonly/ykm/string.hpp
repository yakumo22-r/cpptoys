
/*
socket helper
last date:  2024/4/30
version:    dev 0.0.1
*/
#ifndef YKM_STRING_HPP
#define YKM_STRING_HPP
#include <string>

#ifdef _WIN32
#include <Windows.h>
std::string WIN_ANSIConvert(std::string input, int icp, int ocp) {
    int size_needed = MultiByteToWideChar(icp, 0, input.c_str(), -1, NULL, 0);
    char* widebuffer = new char[size_needed];
    MultiByteToWideChar(icp, 0, input.c_str(), -1, widebuffer, size_needed);

    int out_size_needed = WideCharToMultiByte(ocp, 0, widebuffer, -1, NULL, 0, NULL, NULL);
    char* outbuffer = new char[out_size_needed];
    WideCharToMultiByte(ocp, 0, widebuffer, -1, outbuffer, out_size_needed, NULL, NULL);

    std::string result(outbuffer);
    delete [] widebuffer;
    delete [] outbuffer;
    return std::string(outbuffer);
}
#endif

std::string ansi_convert(std::string input) {
#ifdef _WIN32
    return WIN_ANSIConvert(input, CP_ACP, CP_UTF8);
#else
    return input;
#endif // DEBUG
}

#endif
