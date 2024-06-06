/*
    wrap the glfw as viewbox in mac|linux|windows
   coding
*/
#include "vb_glfw.h"
#include "GLFW/glfw3.h"

struct glfw_global
{
    static void error_callback(int error, const char* description);
    int init_result;
    int last_code;
    std::string last_err;
    glfw_global() : init_result(glfwInit())
    {
        glfwSetErrorCallback(error_callback);
        if (!init_result) //
            ykm_err("glfwInit code({})", init_result);
    }
    operator bool() { return init_result; }

    ~glfw_global() {}
};

glfw_global __glfw;
void glfw_global::error_callback(int error, const char* description)
{
    __glfw.last_code = error;
    __glfw.last_err.clear();
    __glfw.last_err.append(description);
}

namespace ykm
{

int glfw_init = ~int(0);
viewbox::result viewbox::create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title)
{
    _ph = new viewbox_internal::glfw_plat_h();
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    ph.hWnd = nullptr;

    if (!__glfw) { return viewbox::r_internal; }

    ph.hWnd = glfwCreateWindow(sizeX, sizeY, title, nullptr, nullptr);
    if (!ph.hWnd) { return viewbox::r_internal; }
}

YKM_VIEWBOX_RESULT viewbox::show()
{
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    if (!&ph) return r_uninitialized;

    evts.push_evts(viewbox_evt::awake);
    ::ShowWindow(ph->hWnd, SW_SHOW);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_title(const char* title)
{
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    if (!&ph) return r_uninitialized;

    text_title = title;
    ph->state.set(win32_plat_h::d_title);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_pos(int x, int y)
{
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    if (!&ph) return r_uninitialized;
    pos.x = x;
    pos.y = y;
    ph->state.set(win32_plat_h::d_pos);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_size(int x, int y)
{
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    if (!&ph) return r_uninitialized;

    size.x = x;
    size.y = y;
    ph->state.set(win32_plat_h::d_size);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_content_size(int x, int y)
{
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    if (!&ph) return r_uninitialized;

    RECT r;
    r.top = 0;
    r.left = 0;
    r.right = x;
    r.bottom = y;
    content_size.x = x;
    content_size.y = y;

    AdjustWindowRect(&r, ph->style, FALSE);

    size.x = r.right - r.left;
    size.y = r.bottom - r.top;
    ph->state.set(win32_plat_h::d_size);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::hide()
{
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    if (!&ph) return r_uninitialized;

    evts.push_evts(viewbox_evt::sleep);
    ::ShowWindow(ph->hWnd, SW_MINIMIZE);
    return r_ok;
}

YKM_VIEWBOX_VOID viewbox::destory()
{
    ::DestroyWindow(YKM_VIEWBOX_PH(_ph)->hwnd);
    delete YKM_VIEWBOX_PH(_ph);
    _ph = nullptr;
}

YKM_VIEWBOX_I(std::string) viewbox::get_internal_errinfo() const
{

    auto& ph = *YKM_VIEWBOX_PH(_ph);
    if (!&ph) return r_uninitialized;

    return ph ? ph->last_err : "view box impl uninitialized";
}

YKM_VIEWBOX_VOID viewbox::on_fatal_error(int code, const char* title, const char* what) {}

} // namespace ykm
