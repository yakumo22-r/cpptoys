add_requires("glfw")
add_requires("fmt")

option("ykm_viewbox_debug")
    set_default(false)
    set_showmenu(true)
    add_defines("YKM_VIEWBOX_DEBUG")

target("ykm_sys")
    set_kind("static")
    set_languages("c++17")
    add_includedirs("../headonly")
    if is_plat("windows") then
        add_files("sys/sys_win32.cpp")
        add_syslinks("user32")
    end

target("ykm_viewbox")
    set_kind("static")
    set_languages("c++17")
    add_includedirs("../headonly")
    add_includedirs("./include",{public=true})
    add_options("ykm_viewbox_debug")
    add_packages("fmt")
    if is_plat("windows") then
        add_files("viewbox/vb_win32.cpp")
        add_syslinks("user32")
    end

    add_files("sys/input_map.cpp")

target("ykm_app")
    set_kind("static")
    set_languages("c++17")
    --add_includedirs("../headonly")
    add_includedirs("./")
    add_includedirs("./include",{public=true})
    add_options("ykm_viewbox_debug")
    add_packages("fmt")

    add_files("sys/input_map.cpp")
    add_files("app/app.cpp")

    if is_plat("windows") then
        add_files("app/app_win32.cpp")
        add_files("viewbox/vb_win32.cpp")
        add_files("sys/sys_win32.cpp")
        add_syslinks("user32")
    end
