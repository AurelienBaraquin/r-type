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

private:
    std::unordered_map<std::string, std::vector<BindingFunction>> bindings;
};
