#include "ScriptSystem.hpp"

#include <iostream>
#include <mutex>

void ScriptSystem::registerBinding(const std::string& name, BindingFunction func)
{
    std::unique_lock lock(mutex);
    bindings[name].push_back(func);
}

void ScriptSystem::applyBindings(sol::state& luaState)
{
    for (const auto& [name, funcs] : bindings) {
        for (const auto& func : funcs) {
            func(luaState);
        }
    }
}

sol::state& ScriptSystem::getScript(Entity entity, const std::string& scriptPath)
{
    {
        // Check if script already exists
        std::shared_lock lock(mutex);
        auto it = scripts.find({entity, scriptPath});
        if (it != scripts.end()) {
            return it->second;
        }
    }

    // Create and initialize new script

    std::unique_lock lock(mutex);
    auto& luaState = scripts[{entity, scriptPath}];
    initializeScript(luaState, scriptPath);
    return luaState;
}

void ScriptSystem::removeScript(Entity entity, const std::string& scriptPath)
{
    std::unique_lock lock(mutex);
    scripts.erase({entity, scriptPath});
}

void ScriptSystem::initializeScript(sol::state& luaState, const std::string& scriptPath)
{
    luaState.open_libraries(sol::lib::base, sol::lib::math);

    // Apply bindings
    applyBindings(luaState);

    // Load and execute the Lua script
    try {
        luaState.script_file(scriptPath);
    } catch (const std::exception& e) {
        std::cerr << "Failed to load script: " << scriptPath << "\nError: " << e.what()
                  << std::endl;
        throw;
    }
}
