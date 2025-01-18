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
        if (_entityTemplates.find(templateName) == _entityTemplates.end()) {
            Logger::getInstance().error("Entity template not found: " + templateName);
            return Entity();
        }

        Entity entity = registry.createEntity();
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

    std::vector<nlohmann::json> getTemplates() const
    {
        std::vector<nlohmann::json> templates;
        for (const auto& [_, tmpl] : _entityTemplates) {
            templates.push_back(tmpl);
        }
        return templates;
    }

   private:
    std::unordered_map<std::string, nlohmann::json> _entityTemplates;
};
