#include "Core.hpp"
#include "Transform.hpp"

void Engine::registerScriptBindings(ScriptManager& scriptManager, Registry& registry)
{
    (void)scriptManager; // UNUSED !

    _scriptManager.registerBinding("Position", [&registry = registry](sol::state& luaState, Entity entity) {
        luaState["getPosition"] = [&registry, &luaState, entity]() {
            auto* position = registry.getComponent<Components::Position>(entity);
            if (!position)
                throw std::runtime_error("Position component not found");
            return luaState.create_table_with(
                "x", position->x,
                "y", position->y,
                "z", position->z
            );
        };

        luaState["setPosition"] = [&registry, &luaState, entity](sol::table data) {
            auto* position = registry.getComponent<Components::Position>(entity);
            if (!position)
                throw std::runtime_error("Position component not found");
            if (position) {
                position->x = data["x"].get_or(position->x);
                position->y = data["y"].get_or(position->y);
                position->z = data["z"].get_or(position->z);
            }
        };
    });

    _scriptManager.registerBinding("Scale", [&registry = registry](sol::state& luaState, Entity entity) {
        luaState["getScale"] = [&registry, &luaState, entity]() {
            auto* scale = registry.getComponent<Components::Scale>(entity);
            if (!scale)
                throw std::runtime_error("Scale component not found");
            return luaState.create_table_with(
                "x", scale->x,
                "y", scale->y
            );
        };

        luaState["setScale"] = [&registry, &luaState, entity](sol::table data) {
            auto* scale = registry.getComponent<Components::Scale>(entity);
            if (!scale)
                throw std::runtime_error("Scale component not found");
            if (scale) {
                scale->x = data["x"].get_or(scale->x);
                scale->y = data["y"].get_or(scale->y);
            }
        };
    });

    _scriptManager.registerBinding("Rotation", [&registry = registry](sol::state& luaState, Entity entity) {
        luaState["getRotation"] = [&registry, &luaState, entity]() {
            auto* rotation = registry.getComponent<Components::Rotation>(entity);
            if (!rotation)
                throw std::runtime_error("Rotation component not found");
            return luaState.create_table_with(
                "angle", rotation->angle
            );
        };

        luaState["setRotation"] = [&registry, &luaState, entity](sol::table data) {
            auto* rotation = registry.getComponent<Components::Rotation>(entity);
            if (!rotation)
                throw std::runtime_error("Rotation component not found");
            if (rotation) {
                rotation->angle = data["angle"].get_or(rotation->angle);
            }
        };
    });
}
