#include "Scene.hpp"

void SceneLoader::loadEntity(const nlohmann::json& entityData, const std::string& sceneTag)
{
    if (entityData.find("Template") != entityData.end()) {
        _entityTemplateManager.addTemplate(entityData["Template"]);
        return;
    }

    if (entityData.find("FromTemplate") != entityData.end()) {
        Entity entity = _entityTemplateManager.createEntity(entityData["FromTemplate"]["name"],
                                                            registry, factory);
        if (entityData.find("tags") != entityData.end()) {
            for (const auto& tag : entityData["tags"]) {
                registry.addTag(entity, tag);
            }
        }
        registry.addTag(entity, sceneTag);
        return;
    }

    Entity entity = registry.createEntity();
    const auto& components = entityData["components"];

    std::string componentsStr = entityData.dump();
    std::cout << "componentsStr: " << componentsStr << std::endl;
    factory.addComponent(entity, "Json", componentsStr, registry);
    
    for (auto& [componentName, componentData] : components.items()) {
        factory.addComponent(entity, componentName, componentData, registry);
    }

    const auto& tags = entityData["tags"];

    for (const auto& tag : tags) {
        registry.addTag(entity, tag);
    }

    registry.addTag(entity, sceneTag);
}

void SceneLoader::loadScene(const std::string& filePath, bool reload)
{
    path = filePath;
    Logger::getInstance().info("Loading scene: " + filePath);

    std::ifstream file(filePath);
    nlohmann::json sceneData;
    file >> sceneData;
    const std::string sceneTag = sceneData["sceneTag"];

    if (reload) {
        auto entities = registry.getEntitiesByTag(sceneTag);
        for (auto entity : entities) {
            registry.destroyEntity(entity);
        }
    }

    if (sceneData.find("entities") != sceneData.end()) {
        for (const auto& entity : sceneData["entities"]) {
            loadEntity(entity, sceneTag);
        }
    }
    if (!reload) {
        if (sceneData.find("scenes") != sceneData.end()) {
            for (const auto& scene : sceneData["scenes"]) {
                std::filesystem::path scenePath = std::filesystem::path(path).parent_path() / scene;
                SceneLoader(factory, registry, loaderManager, _entityTemplateManager)
                    .loadScene(scenePath.string());
            }
        }
        loaderManager.load(sceneData);
    }
    file.close();
}

void SceneLoader::changeScene(const std::string& filePath)
{
    auto entities = registry.view<>();
    for (auto entity : entities) {
        registry.destroyEntity(entity);
    }
    SceneLoader(factory, registry, loaderManager, _entityTemplateManager).loadScene(filePath);
}