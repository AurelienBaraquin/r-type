#pragma once

#include <functional>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "Log.hpp"
#include "Registry.hpp"

class ComponentFactory
{
   public:
    using ComponentLoader = std::function<void(Entity, const nlohmann::json&, Registry&)>;

    void registerComponent(const std::string& componentName, ComponentLoader loader)
    {
        if (componentLoaders.find(componentName) != componentLoaders.end())
        {
            Logger::getInstance().error("Component " + componentName + " already registered");
            return;
        }
        componentLoaders[componentName] = loader;
    }

    void addComponent(Entity entity, const std::string& componentName,
                      const nlohmann::json& componentData, Registry& registry)
    {
        auto it = componentLoaders.find(componentName);
        if (it != componentLoaders.end())
        {
            it->second(entity, componentData, registry);
        }
        else
        {
            Logger::getInstance().error("Component " + componentName + " not found");
        }
    }

   private:
    std::unordered_map<std::string, ComponentLoader> componentLoaders;
};
