/*
    Integrate views across multiple platforms and export a set of usable interfaces.
    require c++20
*/
#ifndef YKM_VIEWBOX_HPP
#define YKM_VIEWBOX_HPP 


namespace ykm{

struct ViewBox
{
    ViewBox();
};

ViewBox CreateViewBox(){
#ifdef _WIN32
    static_assert(true, "viewbox not implementation on windows platform");
#else
    static_assert(true, "view box not implementation on this platform");
#endif
}


}

#endif
