#include <lua.hpp>

int main() 
{
    lua_State *L = luaL_newstate(); // 创建一个新的Lua环境
    luaL_openlibs(L); // 打开Lua标准库

    // 加载并运行Lua脚本文件
    if (luaL_loadfile(L, "main.lua") || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        return 1;
    }

    lua_close(L); // 关闭Lua环境
    return 0;
}
