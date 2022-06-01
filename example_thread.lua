
local function main()
    common_critical_section:enter()
    common_counter = common_counter or 0
    common_critical_section:exit()
    for _ = 1, 1000000 do
        common_critical_section:enter()
        common_counter = common_counter + 1
        common_critical_section:exit()
    end
    common_critical_section:enter()
    print("thread finished with counter: " .. tostring(common_counter))
    common_critical_section:exit()
end

main()

thread_stopped()
