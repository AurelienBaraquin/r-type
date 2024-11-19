#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "ComponentFactory.hpp"
#include "Registry.hpp"

class SceneLoader
{
   public:
    SceneLoader(ComponentFactory& factory, Registry& registry)
        : factory(factory), registry(registry)
    {
    }

    void loadScene(const std::string& filePath)
    {
        std::ifstream file(filePath);
        nlohmann::json sceneData;
        file >> sceneData;

        for (const auto& entityData : sceneData["entities"])
        {
            Entity entity = registry.createEntity();
            const auto& components = entityData["components"];

            for (auto& [componentName, componentData] : components.items())
            {
                factory.addComponent(entity, componentName, componentData, registry);
            }
        }
    }

    void clear()
    {
        registry.clear();
    }

   private:
    ComponentFactory& factory;
    Registry& registry;
};
