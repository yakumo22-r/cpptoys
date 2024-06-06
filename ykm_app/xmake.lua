add_requires("glfw")
add_requires("fmt")

option("ykm_viewbox_debug")
    set_default(false)
    set_showmenu(true)
    add_defines("YKM_VIEWBOX_DEBUG")

option("ykm_viewbox_glfw")
    set_default(false)
    set_showmenu(true)
option_end()

target("ykm_viewbox")
    set_kind("static")
    set_languages("c++20")
    add_includedirs("../headonly")
    add_includedirs("./include",{public=true})
    add_options("ykm_viewbox_debug")
    add_options("ykm_viewbox_glfw")
    add_packages("fmt")
    if has_config("ykm_viewbox_glfw") then
        add_defines("YKM_VIEWBOX_GLFW")
        add_packages("glfw")
        add_files("viewbox/vb_glfw.cpp")
    elseif is_plat("windows") then
        add_files("viewbox/win32.cpp")
        add_syslinks("user32")
    end

    add_files("sys/input_map.cpp")
