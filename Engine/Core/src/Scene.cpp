#include "Scene.hpp"

void SceneLoader::loadEntity(const nlohmann::json& entityData, const std::string& sceneTag)
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

    registry.addTag(entity, sceneTag);
}

void SceneLoader::loadScene(const std::string& filePath)
{
    path = filePath;

    Logger::getInstance().info("Loading scene: " + filePath);

    std::ifstream file(filePath);
    nlohmann::json sceneData;
    file >> sceneData;

    const std::string sceneTag = sceneData["sceneTag"];

    if (sceneData.find("entities") != sceneData.end())
    {
        for (const auto& entity : sceneData["entities"])
        {
            loadEntity(entity, sceneTag);
        }
    }

    if (sceneData.find("scenes") != sceneData.end())
    {
        for (const auto& scene : sceneData["scenes"])
        {
            std::filesystem::path scenePath = std::filesystem::path(path).parent_path() / scene;
            SceneLoader(factory, registry, loaderManager).loadScene(scenePath.string());
        }
    }

    loaderManager.load(sceneData);
}