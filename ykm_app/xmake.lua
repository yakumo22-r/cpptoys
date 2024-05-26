option("ykm_viewbox_debug")
    set_default(false)
    set_showmenu(true)
    add_defines("YKM_VIEWBOX_DEBUG")

target("ykm_viewbox")
    set_kind("static")
    add_includedirs("../headonly")
    add_includedirs("./include",{public=true})
    add_options("ykm_viewbox_debug")
    add_files("sys/input_map.cpp")
    if is_plat("windows") then
        set_languages("c++20")
        add_files("viewbox/win32.cpp")
        add_syslinks("user32")
    end
