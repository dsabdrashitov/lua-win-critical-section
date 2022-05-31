#include "main.h"

#include <windows.h>


// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
    return TRUE;
}

static const struct luaL_Reg library_functions[] = {
    // Copied project template from winpipe
    // {"winpipe_ByteBlock_setDWORD", winpipe::byteblock::lib_setDWORD},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_wincs(lua_State* L) {
    //winpipe::byteblock::registerMeta(L);
    luaL_newlib(L, library_functions);
    return 1;
}
