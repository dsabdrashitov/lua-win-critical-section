-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwcs = require("build.lua-win-critical-section.lua-win-critical-section")

-- Restore path
package.path = prev_path

function main()
    local cs1 = lwcs.CriticalSection()
    cs1:enter()
    print("Inside critical section cs1")
    lwcs.sleep(2000)
    cs1:exit()

    local cs2 = lwcs.CriticalSection()
    cs1:enter()
    cs2:enter()
    print("Inside critical section cs1&cs2")
    lwcs.sleep(2000)
    cs1:exit()
    cs2:exit()

    cs1:enter()
    cs1:enter()
    print("Inside double critical section cs1")
    lwcs.sleep(2000)
    cs1:exit()
    cs1:exit()
    cs1:exit()
    print("done")
end

main()
