#include "Core.hpp"
#include "Transform.hpp"

void Engine::registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
{
    (void)ScriptSystem;  // UNUSED !

    _ScriptSystem.registerBinding("Position", [&registry = registry](sol::state& luaState) {
        luaState["getPosition"] = [&registry, &luaState](Entity entity) {
            auto* position = registry.getComponent<Components::Position>(entity);
            if (!position)
                throw std::runtime_error("Position component not found at entity " +
                                         std::to_string(entity));
            return luaState.create_table_with("x", position->x, "y", position->y, "z", position->z);
        };

        luaState["setPosition"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* position = registry.getComponent<Components::Position>(entity);
            if (!position)
                throw std::runtime_error("SetPosition: Position component not found at entity " +
                                         std::to_string(entity));
            if (position) {
                position->x = data["x"].get_or(position->x);
                position->y = data["y"].get_or(position->y);
                position->z = data["z"].get_or(position->z);
            }
        };
    });

    _ScriptSystem.registerBinding("Scale", [&registry = registry](sol::state& luaState) {
        luaState["getScale"] = [&registry, &luaState](Entity entity) {
            auto* scale = registry.getComponent<Components::Scale>(entity);
            if (!scale) throw std::runtime_error("Scale component not found");
            return luaState.create_table_with("x", scale->x, "y", scale->y);
        };

        luaState["setScale"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* scale = registry.getComponent<Components::Scale>(entity);
            if (!scale) throw std::runtime_error("Scale component not found");
            if (scale) {
                scale->x = data["x"].get_or(scale->x);
                scale->y = data["y"].get_or(scale->y);
            }
        };
    });

    _ScriptSystem.registerBinding("Rotation", [&registry = registry](sol::state& luaState) {
        luaState["getRotation"] = [&registry, &luaState](Entity entity) {
            auto* rotation = registry.getComponent<Components::Rotation>(entity);
            if (!rotation) throw std::runtime_error("Rotation component not found");
            return luaState.create_table_with("angle", rotation->angle);
        };

        luaState["setRotation"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* rotation = registry.getComponent<Components::Rotation>(entity);
            if (!rotation) throw std::runtime_error("Rotation component not found");
            if (rotation) {
                rotation->angle = data["angle"].get_or(rotation->angle);
            }
        };
    });

    _ScriptSystem.registerBinding("Script", [&registry = registry, &scriptSystem = _ScriptSystem,
                                             this](sol::state& luaState) {
        luaState["hasMethod"] = [&registry, &scriptSystem, &luaState](Entity entity,
                                                                      const std::string& method) {
            auto* script = registry.getComponent<Components::Script>(entity);
            if (!script) return false;

            sol::state& luaState = scriptSystem.getScript(entity, script->scriptPath);
            bool res = luaState[method].valid();
            return res;
        };

        luaState["callMethod"] = [&registry, &luaState, &scriptSystem](Entity entity,
                                                                       const std::string& method,
                                                                       sol::variadic_args va) {
            auto* script = registry.getComponent<Components::Script>(entity);
            if (!script) throw std::runtime_error("Script component not found");
            sol::state& luaState = scriptSystem.getScript(entity, script->scriptPath);
            if (luaState[method].valid()) {
                std::vector<sol::object> args;
//                args.push_back(sol::make_object(luaState, entity));

                for (auto arg : va) {
                    args.push_back(arg);
                }
                luaState[method](sol::as_args(args));
            } else {
                throw std::runtime_error("Method not found");
            }
        };
        luaState["changeScene"] = [this]() {
            std::cout << "loading scene" << std::endl;
            loadScene("Games/RType/config/scene.json",true);

        };
    });

    _ScriptSystem.registerBinding("Entity", [&registry = registry](sol::state& luaState) {
        luaState["getEntitiesByTag"] = [&registry](std::string tag) {
            auto entities = registry.getEntitiesByTag(tag);
            std::vector<Entity> result;
            for (auto entity : entities) {
                result.push_back(entity);
            }
            return result;
        };

        luaState["hasTag"] = [&registry](Entity entity, std::string tag) {
            return registry.hasTag(entity, tag);
        };

        luaState["addTag"] = [&registry](Entity entity, std::string tag) {
            registry.addTag(entity, tag);
        };

        luaState["removeTag"] = [&registry](Entity entity, std::string tag) {
            registry.removeTag(entity, tag);
        };

        luaState["destroyEntity"] = [&registry](sol::object entityObj) {
            if (!entityObj.valid() || entityObj.is<sol::lua_nil_t>()) {
                return;
            }

            Entity entity = entityObj.as<Entity>();
            registry.destroyEntity(entity);
        };
    });

    _ScriptSystem.registerBinding(
        "Template",
        [&registry = this->_registry, &_entityTemplateManager = this->_entityTemplateManager,
         &factory = this->_componentFactory](sol::state& luaState) {
            luaState["createEntity"] = [&_entityTemplateManager, &registry,
                                        &factory](std::string templateName) {
                return _entityTemplateManager.createEntity(templateName, registry, factory);
            };
        });
}
