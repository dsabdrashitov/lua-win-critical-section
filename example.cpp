/**
 * Lua state is not thread-safe, so creating several threads 
 * on the same lua_State is not the right thing. But just for
 * testing purposes I tried and it often works.
 */

#include <windows.h>
#include <stdio.h>
#include <process.h>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#define THREADS_COUNT 4

typedef struct {
    lua_State* L;
    const char* filename;
} ThreadArgs;

static void dofile(void* argsPointer) {
    ThreadArgs args = *((ThreadArgs*) argsPointer);
    lua_State* L = lua_newthread(args.L);
    int ret = luaL_dofile(L, args.filename);
    if (ret == 0) {
        printf("file '%s' executed\n", args.filename);
    } else {
        printf("error %d in file '%s'\n", ret, args.filename);
    }
}

int main(void) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    ThreadArgs args_common_begin = {L, "example_common_begin.lua"};
    dofile(&args_common_begin);
    lua_pushinteger(L, THREADS_COUNT);
    lua_setglobal(L, "threads_to_wait");
    
    for (int i = 0; i < THREADS_COUNT; i++) {
        ThreadArgs args_thread1 = {L, "example_thread.lua"};
        _beginthread(dofile, 0, &args_thread1);
    }
    
    ThreadArgs args_common_end = {L, "example_common_end.lua"};
    dofile(&args_common_end);
    
    lua_close(L);
    printf("Lua closed.\n");
    return 0;
}
