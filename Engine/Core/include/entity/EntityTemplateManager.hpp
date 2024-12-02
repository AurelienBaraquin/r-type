#pragma once

#include <nlohmann/json.hpp>

#include "ComponentFactory.hpp"
#include "Log.hpp"
#include "Registry.hpp"

class EntityTemplateManager
{
   public:
    EntityTemplateManager() = default;

    void addTemplate(const nlohmann::json& data)
    {
        _entityTemplates[data["name"]] = data;
    }

    Entity createEntity(const std::string& templateName, Registry& registry,
                        ComponentFactory& factory)
    {
        Entity entity = registry.createEntity();
        Logger::getInstance().info("Creating entity from template: " + templateName);
        const auto& components = _entityTemplates[templateName]["components"];

        for (auto& [componentName, componentData] : components.items()) {
            factory.addComponent(entity, componentName, componentData, registry);
        }

        if (_entityTemplates[templateName].find("tags") != _entityTemplates[templateName].end()) {
            const auto& tags = _entityTemplates[templateName]["tags"];

            for (const auto& tag : tags) {
                registry.addTag(entity, tag);
            }
        }

        return entity;
    }

   private:
    std::unordered_map<std::string, nlohmann::json> _entityTemplates;
};
