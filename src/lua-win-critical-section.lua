lua_win_critical_section = {}

-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
local wincs = package.loadlib(root_path .. "luawincs.dll", "luaopen_wincs")()

-- Restore path
package.path = prev_path

-- copied project template from winpipe
-- lua_win_pipe.mask = winpipe.winpipe_mask

return lua_win_critical_section