set_languages("c++20")
set_toolchains("clang")-- 设置构建缓存路径

set_targetdir("xmake-build")

target("proxy_test")
add_files("proxy_test.cpp")
