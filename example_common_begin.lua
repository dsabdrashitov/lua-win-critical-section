-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwcs = require("build.lua-win-critical-section.lua-win-critical-section")

-- Restore path
package.path = prev_path

print("lwcs package loaded")


common_critical_section = lwcs.CriticalSection()
threads_to_wait = 0

function thread_stopped()
    common_critical_section:enter()
    threads_to_wait = threads_to_wait - 1
    print("thread stopped (" .. tostring(threads_to_wait) .. ")")
    common_critical_section:exit()
end

function threads_wait()
    while true do
        common_critical_section:enter()
        local count = threads_to_wait
        print("waiting " .. tostring(count))
        common_critical_section:exit()
        if count == 0 then
            break
        else
            lwcs.sleep(100)
        end
    end
end
