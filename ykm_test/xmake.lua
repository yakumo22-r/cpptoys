add_requires("fmt")

target("ykm_test")
    set_kind("static")
    add_includedirs("../ykm_test",{public = true})
    set_toolchains("clang")
    add_packages("fmt",{public=true})
    set_languages("c++20")
    add_files("ykm_test.cpp")
