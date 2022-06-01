#include "sleep.h"

#include <synchapi.h>


namespace wincs::sleep {

int sleep(lua_State* L) {
    DWORD dwMilliseconds = luaL_checkinteger(L, 1);
    Sleep(dwMilliseconds);
    return 0;
}

}
