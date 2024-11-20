#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Entity.hpp"
#include "Script.hpp"

class ScriptSystem
{
   public:
    using BindingFunction = std::function<void(sol::state&)>;

    void registerBinding(const std::string& name, BindingFunction func);
    void applyBindings(sol::state& luaState);
    sol::state& getScript(const std::string& scriptPath);
    void removeScript(const std::string& scriptPath);

   private:
    std::unordered_map<std::string, sol::state> scripts;
    std::unordered_map<std::string, std::vector<BindingFunction>> bindings;
};
