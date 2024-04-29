local conf = {}
-- <internal value>
-- conf.mac         | is mac            (bool)
-- conf.win         | is win            (bool)
-- conf.unix        | is unix           (bool)
-- conf.mac_unix    | is mac or unix    (bool)
-- conf.path        | working path      (string)

-- internal run by neovim

local compile = {
    exec = "clang++",
    sources = {"src/main.cpp", "src/libsftp.cpp"},
    args = {
        "-std=c++20",
        "-I", "lib/include",
        "-I", "include",
        "-L", "lib",
        "-l", "libssh2_static",
        "-l", "ws2_32", -- libssh2 require
        "-o", "sftpdeploy.exe",
    },
}

local compile_shared = {
    exec = "clang++",
    sources = {"src/libsftp.cpp"},
    args = {
        "-std=c++20",
        "-I", "lib/include",
        "-I", "include",
        "-L", "lib",
        "-l", "libssh2_static",
        "-l", "ws2_32", -- libssh2 require
        "-O3 -finline-functions -Os",
        "-shared",
        "-D", "LIBSFTP_SHARED_BUILD",
        "-o", "libsftp.dll",
    },
}
function conf:build(args)
    return self.T.combine_cmds(compile)
end

function conf:build_shared(args)
    return self.T.combine_cmds(compile_shared)
end

function conf:build_info(args)
    self.T.cxx_compile_flags(compile)
end

conf.run = {cmd = "sftpdeploy"}


return conf
