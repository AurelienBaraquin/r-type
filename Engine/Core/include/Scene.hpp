#pragma once

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "ComponentFactory.hpp"
#include "Loader.hpp"
#include "Log.hpp"
#include "Registry.hpp"

class SceneLoader : public ILoader
{
   public:
    SceneLoader(ComponentFactory& factory, Registry& registry, LoaderManager& loaderManager)
        : factory(factory), registry(registry), loaderManager(loaderManager)
    {
    }

    void load(const std::string& filePath) override
    {
        Logger::getInstance().info("Loading scene: " + filePath);

        std::ifstream file(filePath);
        nlohmann::json sceneData;
        file >> sceneData;

        std::string sceneTag = sceneData["sceneTag"];

        for (const auto& entityData : sceneData["entities"])
        {
            Entity entity = registry.createEntity();
            const auto& components = entityData["components"];

            for (auto& [componentName, componentData] : components.items())
            {
                factory.addComponent(entity, componentName, componentData, registry);
            }

            const auto& tags = entityData["tags"];

            for (const auto& tag : tags)
            {
                registry.addTag(entity, tag);
            }

            registry.addTag(entity, sceneTag + "_scene");
        }

        if (sceneData.find("scenes") != sceneData.end())
        {
            for (const auto& scene : sceneData["scenes"])
            {
                std::filesystem::path scenePath =
                    std::filesystem::path(filePath).parent_path() / scene;
                SceneLoader(factory, registry, loaderManager).load(scenePath.string());
            }
        }

        loaderManager.load(filePath);
    }

    void clear()
    {
        registry.clear();
    }

   private:
    ComponentFactory& factory;
    Registry& registry;
    LoaderManager& loaderManager;
};
