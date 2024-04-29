//#include "libsftp.hpp"
#include "libsftp.h"
#include <exception>
#include <format>
#include <iostream>
#include <thread>
#include "ykm_thread_tool.hpp"
#include <atomic>

struct A{
    int i;
    std::string s;
};

struct B{
    int i;
    std::string s;
};

ykm::LockQueue<A> input;
ykm::LockQueue<B> output;
std::atomic<bool> e;
void thr(){
    while (!e) {
        int i = input.pop().i;
        output.push({i});
        if (i < 0){
            e = true;
        }
    }
}

int main()
{
        libsftp_async_handle ah = libsftp_make_async_handle();
        auto ac = libsftp_async_start(ah, "120.79.29.215", 22, "root", "xytest@root02.xy20201231");
        std::cout << "next" <<std::endl;
        int state = 200;
        libsftp_async_done(ac);
        while (state != 0) {
            state = libsftp_async_state(ac).state;
        }

    return 0;
}
