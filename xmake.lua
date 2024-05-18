set_languages("c++20")
set_toolchains("clang")

target("ytest")
add_includedirs("./headonly")
add_files("./test/ytest.cpp")
