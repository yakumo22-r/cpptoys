set_languages("c++20")
set_toolchains("clang")

add_requires("luajit")

target("test_lua")
    add_files("test_lua.cpp")
    set_targetdir("$(projectdir)/xmake-build")
    add_packages("luajit")

target("ytest")
    add_includedirs("../headonly")
    add_deps("ykm_test")
    set_targetdir("$(projectdir)/xmake-build")
    add_files("./ytest.cpp")

target("vbox")
    add_includedirs("../headonly")
    add_deps("ykm_viewbox")
    set_targetdir("$(projectdir)/xmake-build")
    add_files("./vbox.cpp")
