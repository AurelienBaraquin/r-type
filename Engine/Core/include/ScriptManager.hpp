#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Entity.hpp"
#include "Script.hpp"

class ScriptManager
{
   public:
    using BindingFunction = std::function<void(sol::state&)>;

    void registerBinding(const std::string& name, BindingFunction func)
    {
        bindings[name].push_back(func);
    }

    void applyBindings(sol::state& luaState)
    {
        for (auto& [name, funcs] : bindings)
        {
            for (auto& func : funcs)
            {
                func(luaState);
            }
        }
    }

    sol::state& getScript(const std::string& scriptPath)
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

    void removeScript(const std::string& scriptPath)
    {
        scripts.erase(scriptPath);
    }

   private:
    std::unordered_map<std::string, sol::state> scripts;
    std::unordered_map<std::string, std::vector<BindingFunction>> bindings;
};
