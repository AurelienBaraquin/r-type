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

sol::state& ScriptSystem::getScript(Entity entity, const std::string& scriptPath)
{
    if (scripts.find({entity, scriptPath}) == scripts.end())
    {
        scripts[{entity, scriptPath}] = sol::state();
        scripts[{entity, scriptPath}].open_libraries(sol::lib::base, sol::lib::math);
        applyBindings(scripts[{entity, scriptPath}]);
        scripts[{entity, scriptPath}].script_file(scriptPath);
    }

    return scripts[{entity, scriptPath}];
}

void ScriptSystem::removeScript(Entity entity, const std::string& scriptPath)
{
    scripts.erase({entity, scriptPath});
}
