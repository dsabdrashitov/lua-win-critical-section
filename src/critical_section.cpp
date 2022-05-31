#include "critical_section.h"

#include <synchapi.h>


namespace wincs::critical_section {

static const char* METATABLE_NAME = "wincs.critical_section";

static int CriticalSection_gc(lua_State* L);
static int CriticalSection_enter(lua_State* L);
static int CriticalSection_exit(lua_State* L);

void registerMeta(lua_State* L) {
    luaL_newmetatable(L, METATABLE_NAME);
    // set __gc
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, CriticalSection_gc);
    lua_settable(L, -3);
    // set __index to self
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    // set enter method
    lua_pushstring(L, "enter");
    lua_pushcfunction(L, CriticalSection_enter);
    lua_settable(L, -3);
    // set exit method
    lua_pushstring(L, "exit");
    lua_pushcfunction(L, CriticalSection_exit);
    lua_settable(L, -3);
    // remove metatable from stack
    lua_settop(L, -1);
}

int CriticalSection_new(lua_State* L) {
    CRITICAL_SECTION* cs = (CRITICAL_SECTION*) lua_newuserdata(L, sizeof(CRITICAL_SECTION));
    luaL_getmetatable(L, METATABLE_NAME);
    lua_setmetatable(L, -2);
    InitializeCriticalSection(cs);
    return 1;
}

static int CriticalSection_gc(lua_State* L) {
    CRITICAL_SECTION* cs = (CRITICAL_SECTION*) luaL_checkudata(L, 1, METATABLE_NAME);
    DeleteCriticalSection(cs);
    return 0;
}

static int CriticalSection_enter(lua_State* L) {
    CRITICAL_SECTION* cs = (CRITICAL_SECTION*) lua_touserdata(L, 1);
    EnterCriticalSection(cs);
    return 0;
}

static int CriticalSection_exit(lua_State* L) {
    CRITICAL_SECTION* cs = (CRITICAL_SECTION*) lua_touserdata(L, 1);
    LeaveCriticalSection(cs);
    return 0;
}

}
