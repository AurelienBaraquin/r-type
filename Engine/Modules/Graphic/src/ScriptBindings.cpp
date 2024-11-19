#include "Graphic.hpp"

void Graphic::registerScriptBindings(ScriptManager& scriptManager, Registry& registry) {
    scriptManager.registerBinding("Sprite", [&registry = registry](sol::state& luaState) {
        luaState["getSprite"] = [&registry, &luaState](Entity entity) {
            auto* sprite = registry.getComponent<Components::Sprite>(entity);
            if (!sprite)
                throw std::runtime_error("Sprite component not found");
            return luaState.create_table_with(
                "textureID", sprite->textureID,
                "width", sprite->width,
                "height", sprite->height,
                "originX", sprite->originX,
                "originY", sprite->originY
            );
        };

        luaState["setSprite"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* sprite = registry.getComponent<Components::Sprite>(entity);
            if (!sprite)
                throw std::runtime_error("Sprite component not found");
            if (sprite) {
                sprite->textureID = data["textureID"].get_or(sprite->textureID);
                sprite->width = data["width"].get_or(sprite->width);
                sprite->height = data["height"].get_or(sprite->height);
                sprite->originX = data["originX"].get_or(sprite->originX);
                sprite->originY = data["originY"].get_or(sprite->originY);
            }
        };
    });

    scriptManager.registerBinding("Position", [&registry = registry](sol::state& luaState) {
        luaState["getPosition"] = [&registry, &luaState](Entity entity) {
            auto* position = registry.getComponent<Components::Position>(entity);
            if (!position)
                throw std::runtime_error("Position component not found");
            return luaState.create_table_with(
                "x", position->x,
                "y", position->y,
                "z", position->z
            );
        };

        luaState["setPosition"] = [&registry, &luaState](Entity entity, sol::table data) {
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
}
