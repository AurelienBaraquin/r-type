#include "Graphic.hpp"

void Graphic::registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
{
    ScriptSystem.registerBinding("Sprite", [&registry = registry](sol::state& luaState) {
        luaState["getSprite"] = [&registry, &luaState](Entity entity) {
            auto* sprite = registry.getComponent<Components::Sprite>(entity);
            if (!sprite) throw std::runtime_error("Sprite component not found");
            return luaState.create_table_with("spriteID", sprite->spriteID);
        };

        luaState["setSprite"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* sprite = registry.getComponent<Components::Sprite>(entity);
            if (!sprite) throw std::runtime_error("Sprite component not found");
            if (sprite) {
                sprite->spriteID = data["spriteID"].get_or(sprite->spriteID);
            }
        };
    });

    ScriptSystem.registerBinding("Animation", [&registry = registry](sol::state& luaState) {
        luaState["getAnimation"] = [&registry, &luaState](Entity entity) {
            auto* animation = registry.getComponent<Components::Animation>(entity);
            if (!animation) throw std::runtime_error("Animation component not found");
            return luaState.create_table_with(
                "animationID", animation->animationID, "currentFrame", animation->currentFrame,
                "elapsedTime", animation->elapsedTime, "frameTime", animation->frameTime, "playing",
                animation->playing, "loop", animation->loop);
        };

        luaState["setAnimation"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* animation = registry.getComponent<Components::Animation>(entity);
            if (!animation) throw std::runtime_error("Animation component not found");
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

    ScriptSystem.registerBinding("Animation", [&registry = registry,
                                               &_AnimationSystem =
                                                   _AnimationSystem](sol::state& luaState) {
        luaState["playAnimation"] = [&registry, &_AnimationSystem](Entity entity, int animationID) {
            auto* animation = registry.getComponent<Components::Animation>(entity);
            if (!animation) throw std::runtime_error("Animation component not found");
            _AnimationSystem.playAnimation(animationID, *animation);
        };
    });

    ScriptSystem.registerBinding(
        "Animation",
        [&registry = registry, &_AnimationSystem = _AnimationSystem](sol::state& luaState) {
            luaState["stopAnimation"] = [&registry, &_AnimationSystem](Entity entity) {
                auto* animation = registry.getComponent<Components::Animation>(entity);
                if (!animation) throw std::runtime_error("Animation component not found");
                _AnimationSystem.stopAnimation(*animation);
            };
        });
}
