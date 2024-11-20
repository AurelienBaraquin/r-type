#include "ScriptSystem.hpp"

void ScriptSystem::registerBinding(const std::string& name, BindingFunction func)
{
    bindings[name].push_back(func);
}

void ScriptSystem::applyBindings(sol::state& luaState)
{
    for (auto& [name, funcs] : bindings)
    {
        for (auto& func : funcs)
        {
            func(luaState);
        }
    }
}

sol::state& ScriptSystem::getScript(const std::string& scriptPath)
{
    if (scripts.find(scriptPath) == scripts.end())
    {
        scripts[scriptPath] = sol::state();
        scripts[scriptPath].open_libraries(sol::lib::base, sol::lib::math);
        applyBindings(scripts[scriptPath]);
        scripts[scriptPath].script_file(scriptPath);
    }

    return scripts[scriptPath];
}

void ScriptSystem::removeScript(const std::string& scriptPath)
{
    scripts.erase(scriptPath);
}
