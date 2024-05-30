#include <iostream>

#include "ykm_dylib_vk.h"

YKM_DYLIB_VK_DEF_LOADER;

int main()
{
    std::cout << "ok?" << std::endl;
    init_vk_loader();
    std::cout << "ok!" << std::endl;
    return 0; 
};
