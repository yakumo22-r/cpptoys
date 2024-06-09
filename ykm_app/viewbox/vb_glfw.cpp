/*
    wrap the glfw as viewbox in mac|linux|windows
   coding
*/
#include "vb_glfw.h"
#include "GLFW/glfw3.h"
#include "debug.hpp"
#include "event.hpp"
#include <../sys/input_def.hpp>
#include <memory>
#include <unordered_set>
#include <vector>

using namespace ykm::app;

struct glfw_global
{
  public:
    static void error_callback(int error, const char* description);

    glfw_global()
        : //
          init_result(glfwInit()),
          last_code(0),
          last_err(),
          all_wnds(),
          process_count(0)
    {
        glfwSetErrorCallback(error_callback);
        if (!init_result) //
            ykm_err("glfwInit code({})", init_result);
        else
            ykm_log("glfw init success");
    }

    void poll_events()
    {
        process_count++;
        if (process_count >= all_wnds.size())
        {
            glfwPollEvents();
            process_count = 0;
        }
    }

    operator bool() { return init_result; }

    void register_wnd(ykm::viewbox* p)
    {
        if (!all_wnds.count(p)) { all_wnds.insert(p); }
    }
    void unregister_wnd(ykm::viewbox* p)
    {
        if (all_wnds.count(p)) { all_wnds.erase(p); }
    }
    int get_wnds_num() const { return all_wnds.size(); }

    ~glfw_global()
    {
        glfwTerminate();
        ykm_log("glfw terminate");
    }

  public:
    int init_result;
    int last_code;
    std::string last_err;

  private:
    std::unordered_set<ykm::viewbox*> all_wnds;
    int process_count = 0;
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto user_pointer = glfwGetWindowUserPointer(window);
    if (!user_pointer) return;
    auto& ph = *YKM_VIEWBOX_PH(user_pointer);

    if (action == GLFW_PRESS)
        ph.evts().keyboard.press(input::kc_by_sc(scancode));
    else
        ph.evts().keyboard.release(input::kc_by_sc(scancode));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto user_pointer = glfwGetWindowUserPointer(window);
    if (!user_pointer) return;
    auto& ph = *YKM_VIEWBOX_PH(user_pointer);

    if (action == GLFW_PRESS)
        ph.evts().mouse.press(input::mouse_evt(button + 1));
    else
        ph.evts().mouse.release(input::mouse_evt(button + 1));
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto user_pointer = glfwGetWindowUserPointer(window);
    if (!user_pointer) return;
    auto& ph = *YKM_VIEWBOX_PH(user_pointer);

    // ykm_log("{} mouse move {} {}", ph.vb->title(), xpos,ypos);
    ph.evts().mouse.x() = (int)xpos;
    ph.evts().mouse.y() = (int)ypos;
    ph.evts().mouse.press(input::mouse_evt::move);
}

void wheel_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto user_pointer = glfwGetWindowUserPointer(window);
    if (!user_pointer) return;
    auto& ph = *YKM_VIEWBOX_PH(user_pointer);

    ph.evts().mouse.press(input::mouse_evt::scroll);
    ph.evts().mouse.scroll_x() = (int)(xoffset * 10);
    ph.evts().mouse.scroll_y() = (int)(yoffset * 10);
}

void window_pos_callback(GLFWwindow* window, int x, int y)
{
    auto user_pointer = glfwGetWindowUserPointer(window);
    if (!user_pointer) return;
    auto& ph = *YKM_VIEWBOX_PH(user_pointer);

    auto pos = ph.ltpos_2_pos({x, y});

    if (pos != ph.pos())
    {
        ph.evts().push_evts(viewbox_evt::move);
        ph.pos() = pos;
        ykm_log("{} pos {} {}", ph.title(), pos.x, pos.y);
    }
}

void window_size_callback(GLFWwindow* window, int x, int y)
{
    auto user_pointer = glfwGetWindowUserPointer(window);
    if (!user_pointer) return;
    auto& ph = *YKM_VIEWBOX_PH(user_pointer);

    auto pos = ph.ltpos_2_pos({x, y});

    ph.evts().push_evts(viewbox_evt::resize);
    ph.content_size() = {x, y};

    ph.size() = {ph.frame_size.x + x, ph.frame_size.y + y};

    ykm_log("{} resize {} {}", ph.title(), ph.content_size().x, ph.content_size().y);
}

void window_focus_callback(GLFWwindow* window, int focusd)
{
    auto user_pointer = glfwGetWindowUserPointer(window);
    if (!user_pointer) return;
    auto& ph = *YKM_VIEWBOX_PH(user_pointer);

    if (focusd) //
    {
        ph.evts().push_evts(viewbox_evt::active);
    }
    else //
    {
        ph.evts().push_evts(viewbox_evt::unactive);
    }
}

viewbox::result viewbox::create(int32_t posX, int32_t posY, int32_t sizeX, int32_t sizeY, const char* title)
{
    if (!__glfw) { return viewbox::r_internal; }

    _ph = new viewbox_internal::glfw_plat_h();
    auto& ph = *YKM_VIEWBOX_PH(_ph);
    ph.vb = this;
    ph.hWnd = nullptr;

    ph.hWnd = glfwCreateWindow(sizeX, sizeY, title, nullptr, nullptr);

    if (!ph.hWnd) { return viewbox::r_internal; }

    {
        int f_left, f_top, f_right, f_bottom;
        glfwGetWindowFrameSize(ph.hWnd, &f_left, &f_top, &f_right, &f_bottom);

        float wfs_w = f_right - f_left;
        float wfs_h = f_bottom - f_top;

        int fbs_w, fbs_h;
        glfwGetFramebufferSize(ph.hWnd, &fbs_w, &fbs_h);

        ph.pt_ratio = {fbs_w / wfs_w, fbs_h / wfs_h};
        ph.frame_size = ph.pt2px({f_right - f_left, f_bottom - f_top});
    }

    size = {ph.frame_size.x + content_size.x, ph.frame_size.y + content_size.y};

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    ph.screen_half = ph.pt2px({mode->width / 2, mode->height / 2});

    pos = {posX, posY};
    content_size = {sizeX, sizeY};

    ph.lt_pos = ph.pos_2_ltpos(pos);
    ph.state.set(wnd_state::d_size);

    glfwSetWindowUserPointer(ph.hWnd, _ph);
    glfwSetKeyCallback(ph.hWnd, key_callback);
    glfwSetMouseButtonCallback(ph.hWnd, mouse_button_callback);
    // glfwSetCursorEnterCallback(ph.hWnd, cursor_enter_callback);
    glfwSetCursorPosCallback(ph.hWnd, cursor_pos_callback);
    glfwSetScrollCallback(ph.hWnd, wheel_callback);

    glfwSetWindowPosCallback(ph.hWnd, window_pos_callback);
    glfwSetWindowSizeCallback(ph.hWnd, window_size_callback);
    glfwSetWindowFocusCallback(ph.hWnd, window_focus_callback);

    __glfw.register_wnd(this);

    return r_ok;
}

viewbox::result viewbox::process_loop()
{
    if (!_ph) return r_uninitialized;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    ph.evts().clear_evts();
    ph.evts().keyboard.next_frame();
    ph.evts().mouse.clear();

    __glfw.poll_events();

    if (ph.state.test(wnd_state::d_size) || ph.state.test(wnd_state::d_pos))
    {
        auto v = ph.pt2px(content_size);
        glfwSetWindowSize(ph.hWnd, v.x, v.y);
        v = ph.pt2px(ph.lt_pos);
        glfwSetWindowPos(ph.hWnd, v.x, v.y);
        ph.state.reset(wnd_state::d_size);
        ph.state.reset(wnd_state::d_pos);
    }

    if (ph.state.test(wnd_state::d_title))
    {
        glfwSetWindowTitle(ph.hWnd, text_title.c_str());
        ph.evts().push_evts(viewbox_evt::title);
        ph.state.reset(wnd_state::d_title);
    }

    if (glfwWindowShouldClose(ph.hWnd))
    {
        this->destory();
        return r_quit;
    }
    return r_ok;
}

viewbox::result viewbox::show()
{
    if (!_ph) return r_uninitialized;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    evts.push_evts(viewbox_evt::awake);
    glfwShowWindow(ph.hWnd);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_title(const char* title)
{
    if (!_ph) return r_uninitialized;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    text_title = title;
    ph.state.set(wnd_state::d_title);
    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_pos(int x, int y)
{
    if (!_ph) return r_uninitialized;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    pos = {x, y};
    ph.lt_pos = ph.pos_2_ltpos(pos);

    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_size(int x, int y)
{
    if (!_ph) return r_uninitialized;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    content_size = {
        x - ph.frame_size.x,
        y - ph.frame_size.y,
    };
    size = {x, y};

    ph.lt_pos = ph.pos_2_ltpos(pos);

    ph.state.set(wnd_state::d_size);

    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::set_content_size(int x, int y)
{
    if (!_ph) return r_uninitialized;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    size = {
        x + ph.frame_size.x,
        y + ph.frame_size.y,
    };
    content_size = {x, y};

    ph.lt_pos = ph.pos_2_ltpos(pos);

    ph.state.set(wnd_state::d_size);

    return r_ok;
}

YKM_VIEWBOX_RESULT viewbox::hide()
{
    if (!_ph) return r_uninitialized;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    evts.push_evts(viewbox_evt::sleep);
    glfwHideWindow(ph.hWnd);
    return r_ok;
}

YKM_VIEWBOX_VOID viewbox::destory()
{
    if (!_ph) return;
    auto& ph = *YKM_VIEWBOX_PH(_ph);

    __glfw.unregister_wnd(this);
    glfwDestroyWindow(ph.hWnd);
    delete YKM_VIEWBOX_PH(_ph);
    _ph = nullptr;
}

YKM_VIEWBOX_I(std::string) viewbox::get_internal_errinfo() const { return __glfw.last_err; }

YKM_VIEWBOX_VOID viewbox::on_fatal_error(int code, const char* title, const char* what) {}

} // namespace ykm
