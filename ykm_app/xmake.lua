add_requires("glfw")
add_requires("fmt")

option("ykm_viewbox_debug")
    set_default(false)
    set_showmenu(true)
    add_defines("YKM_VIEWBOX_DEBUG")

local function ykm_app_proj(basename,kind)
    set_languages("c++17")
    add_includedirs("./")
    add_includedirs("./include",{public=true})
    add_options("ykm_viewbox_debug")
    add_packages("fmt")
    set_basename(basename)
    set_kind(kind)
end

local function ykm_app_app()
    add_files("app/app.cpp")

    if is_plat("windows") then
        add_files("app/app_win32.cpp")
        add_files("viewbox/vb_win32.cpp")
        add_syslinks("user32")
    end
end

local function ykm_app_sys()
    add_files("sys/input_map.cpp")

    if is_plat("windows") then
        add_files("sys/sys_win32.cpp")
        add_syslinks("user32","gdi32")
    end
end

target("ykm_app")
    ykm_app_proj("ykm_app","static")

    ykm_app_app()
    ykm_app_sys()

target("ykm_app_dylib")
    ykm_app_proj("ykm_app", "shared")

    ykm_app_app()
    add_defines("YKM_APP_SHARED_BUILD",{public=false})
    add_defines("YKM_APP_SHARED_LIB",{public=true})

    ykm_app_sys()
    add_defines("YKM_SYS_SHARED_BUILD",{public=false})
    add_defines("YKM_SYS_SHARED_LIB",{public=true})

target("ykm_app_app")
    ykm_app_proj("ykm_app_app", "static")

    ykm_app_app()


target("ykm_app_app_dylib")
    ykm_app_proj("ykm_app_app", "shared")

    ykm_app_app()
    add_defines("YKM_APP_SHARED_BUILD",{public=false})
    add_defines("YKM_APP_SHARED_LIB",{public=true})


target("ykm_app_sys")
    ykm_app_proj("ykm_app_sys", "static")
    add_deps("ykm_app_app")

    ykm_app_sys()

target("ykm_app_sys_dylib")
    ykm_app_proj("ykm_app_sys", "static")
    add_deps("ykm_app_app_dylib")

    ykm_app_sys()
    add_defines("YKM_SYS_SHARED_BUILD",{public=false})
    add_defines("YKM_SYS_SHARED_LIB",{public=true})
