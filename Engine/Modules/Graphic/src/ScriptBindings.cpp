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

    scriptManager.registerBinding("Animation", [&registry = registry](sol::state& luaState) {
        luaState["getAnimation"] = [&registry, &luaState](Entity entity) {
            auto* animation = registry.getComponent<Components::Animation>(entity);
            if (!animation)
                throw std::runtime_error("Animation component not found");
            return luaState.create_table_with(
                "animationID", animation->animationID,
                "currentFrame", animation->currentFrame,
                "elapsedTime", animation->elapsedTime,
                "frameTime", animation->frameTime,
                "playing", animation->playing,
                "loop", animation->loop
            );
        };

        luaState["setAnimation"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* animation = registry.getComponent<Components::Animation>(entity);
            if (!animation)
                throw std::runtime_error("Animation component not found");
            if (animation) {
                animation->animationID = data["animationID"].get_or(animation->animationID);
                animation->currentFrame = data["currentFrame"].get_or(animation->currentFrame);
                animation->elapsedTime = data["elapsedTime"].get_or(animation->elapsedTime);
                animation->frameTime = data["frameTime"].get_or(animation->frameTime);
                animation->playing = data["playing"].get_or(animation->playing);
                animation->loop = data["loop"].get_or(animation->loop);
            }
        };
    });

    scriptManager.registerBinding("Animation", [&registry = registry, &_animationManager = _animationManager](sol::state& luaState) {
        luaState["playAnimation"] = [&registry, &_animationManager](Entity entity, int animationID) {
            auto* animation = registry.getComponent<Components::Animation>(entity);
            if (!animation)
                throw std::runtime_error("Animation component not found");
            _animationManager.playAnimation(animationID, *animation);
        };
    });

    scriptManager.registerBinding("Animation", [&registry = registry, &_animationManager = _animationManager](sol::state& luaState) {
        luaState["stopAnimation"] = [&registry, &_animationManager](Entity entity) {
            auto* animation = registry.getComponent<Components::Animation>(entity);
            if (!animation)
                throw std::runtime_error("Animation component not found");
            _animationManager.stopAnimation(*animation);
        };
    });
}
