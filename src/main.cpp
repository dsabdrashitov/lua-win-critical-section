#include "main.h"

#include <windows.h>
#include "critical_section.h"


// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
    return TRUE;
}

static const struct luaL_Reg library_functions[] = {
    {"CriticalSection_new", wincs::critical_section::CriticalSection_new},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_wincs(lua_State* L) {
    wincs::critical_section::registerMeta(L);
    luaL_newlib(L, library_functions);
    return 1;
}
