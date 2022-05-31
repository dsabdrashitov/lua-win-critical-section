#ifndef LUAWINCS_CRITICAL_SECTION_H
#define LUAWINCS_CRITICAL_SECTION_H

#include "common.h"

namespace wincs::critical_section {

void registerMeta(lua_State* L);

int CriticalSection_new(lua_State* L);

}

#endif
