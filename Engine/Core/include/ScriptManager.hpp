#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include "Script.hpp"
#include "Entity.hpp"

class ScriptManager {
public:
    using BindingFunction = std::function<void(sol::state&, Entity)>;

    void registerBinding(const std::string& name, BindingFunction func) {
        bindings[name].push_back(func);
    }

    void applyBindings(sol::state& luaState, Entity entity) {
        for (auto& [name, funcs] : bindings) {
            for (auto& func : funcs) {
                func(luaState, entity);
            }
        }
    }

    sol::state& getScript(const std::string& scriptPath, Entity entity)
    {
        if (scripts.find(scriptPath) == scripts.end())
        {
            scripts[scriptPath] = sol::state();
            scripts[scriptPath].open_libraries(sol::lib::base, sol::lib::math);
            applyBindings(scripts[scriptPath], entity);
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
