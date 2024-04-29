local conf = {}
-- <internal value>
-- conf.mac         | is mac            (bool)
-- conf.win         | is win            (bool)
-- conf.unix        | is unix           (bool)
-- conf.mac_unix    | is mac or unix    (bool)
-- conf.path        | working path      (string)

-- internal run by neovim

function conf:build(args)

end

--conf.run.cmd = "echo run_no_inplementation"
--conf.run.terminal = "default" -- system | toggle


local compile_ser = {
    exec = "clang++",
    sources = {"serpack_test.cpp"},
    args = {
        "-std=c++20",
        "-I", "headonly",
        "-o", "serpack_test.exe",
    },
}

function conf:build_info(args)
    self.T.cxx_compile_flags(compile_ser)
end

function conf:build_ser(args)
    local cmd = self.T.combine_cmds(compile_ser);
    return cmd.." && ".."serpack_test.exe", "toggle"
end


return conf
