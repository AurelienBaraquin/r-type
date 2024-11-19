#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Registry.hpp"

class ComponentFactory {
public:
    using ComponentLoader = std::function<void(Entity, const nlohmann::json&, Registry&)>;

    void registerComponent(const std::string& componentName, ComponentLoader loader) {
        componentLoaders[componentName] = loader;
    }

    void addComponent(Entity entity, const std::string& componentName, const nlohmann::json& componentData, Registry& registry) {
        auto it = componentLoaders.find(componentName);
        if (it != componentLoaders.end()) {
            it->second(entity, componentData, registry);
        } else {
            throw std::runtime_error("Component '" + componentName + "' is not registered.");
        }
    }

private:
    std::unordered_map<std::string, ComponentLoader> componentLoaders;
};
