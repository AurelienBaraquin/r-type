#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <shared_mutex>

#include "Entity.hpp"
#include "Script.hpp"

class ScriptSystem {
public:
    using BindingFunction = std::function<void(sol::state&)>;

    void registerBinding(const std::string& name, BindingFunction func);
    void applyBindings(sol::state& luaState);
    sol::state& getScript(Entity entity, const std::string& scriptPath);
    void removeScript(Entity entity, const std::string& scriptPath);

private:
    struct PairHash {
        template <typename T1, typename T2>
        std::size_t operator()(const std::pair<T1, T2>& pair) const {
            std::size_t hash1 = std::hash<T1>{}(pair.first);
            std::size_t hash2 = std::hash<T2>{}(pair.second);
            return hash1 ^ (hash2 << 1);
        }
    };

    mutable std::shared_mutex mutex;

    // Entity ID, ScriptPath -> Lua state
    std::unordered_map<std::pair<Entity, std::string>, sol::state, PairHash> scripts;
    std::unordered_map<std::string, std::vector<BindingFunction>> bindings;

    void initializeScript(sol::state& luaState, const std::string& scriptPath);
};
