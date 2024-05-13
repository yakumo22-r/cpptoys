set_languages("c++20")
set_toolchains("clang")-- 设置构建缓存路径

target("ytest")
add_includedirs("./headonly")
add_files("./test/ytest.cpp")
