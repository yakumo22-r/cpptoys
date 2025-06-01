add_requires("glfw")
add_requires("fmt")

local AppOpt = {
    Ex_Viewbox = "ykm_app_opt_viewbox",
    Debug_Viewbox = "ykm_app_opt_viewbox_debug",
}


option(AppOpt.Ex_Viewbox)
set_default(false)
set_showmenu(true)
set_description("Enable viewbox module")
add_defines("YKM_APP_OPT_VIEWBOX")

option(AppOpt.Debug_Viewbox)
set_default(false)
set_showmenu(true)
add_defines("YKM_VIEWBOX_DEBUG")

-- ykm_app (Mother module)
local function ykm_app(basename, kind)
    set_languages("c++17")
    add_packages("fmt")
    set_basename(basename)
    set_kind(kind)
    add_options(AppOpt.Ex_Viewbox)
    add_options(AppOpt.Debug_Viewbox)

    add_includedirs("./")
    add_includedirs("./include", { public = true })
    add_files("app/app.cpp", "app/sys.cpp", "app/input_map.cpp")

    if is_plat("windows") then
        add_files("app/app_win32.cpp", "app/sys_win32.cpp")
        add_syslinks("user32", "gdi32")
    end

    if has_config(AppOpt.Ex_Viewbox) then
        if is_plat("windows") then
            add_files("app/viewbox/vb_win32.cpp")
        end
    end
end

target("ykm_app")
ykm_app("ykm_app_static", "static")

target("ykm_app_dylib")
ykm_app("ykm_app", "shared")
add_defines("YKM_APP_SHARED_BUILD", { public = false })
add_defines("YKM_APP_SHARED_LIB", { public = true })
