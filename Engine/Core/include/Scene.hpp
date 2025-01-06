#pragma once

#include <filesystem>
#include <string>

#include "ComponentFactory.hpp"
#include "EntityTemplateManager.hpp"
#include "Loader.hpp"
#include "Log.hpp"
#include "Registry.hpp"

class SceneLoader
{
   public:
    SceneLoader(ComponentFactory& factory, Registry& registry, LoaderManager& loaderManager,
                EntityTemplateManager& entityTemplateManager)
        : factory(factory),
          registry(registry),
          loaderManager(loaderManager),
          _entityTemplateManager(entityTemplateManager)
    {
    }

    void loadEntity(const nlohmann::json& entityData, const std::string& sceneTag);
    void loadScene(const std::string& filePath, bool reload = false);
    void changeScene(const std::string& filePath);
    void clear()
    {
        registry.clear();
    }

   private:
    std::string path;
    ComponentFactory& factory;
    Registry& registry;
    LoaderManager& loaderManager;
    EntityTemplateManager& _entityTemplateManager;
};
