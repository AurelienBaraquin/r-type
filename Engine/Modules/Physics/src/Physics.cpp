//
// Created by Guillaume Tran on 19/11/2024.
//

#include "Physics.hpp"

#include <typeinfo>

#include "Area2D.hpp"
#include "Transform.hpp"

struct CollisionInfo {
    Entity entity1;
    Entity entity2;
    bool isEntering;
};

void Physics::callFunction(Registry& registry, Entity entity, Entity entity2, std::string function,
                           ScriptSystem& _scriptSystem)
{
    auto* script = registry.getComponent<Components::Script>(entity);
    if (script && script->initialized && script->scriptPath != "" && script->initialized &&
        _scriptSystem.hasScript(entity, script->scriptPath)) {
        sol::state& luaState = _scriptSystem.getScript(entity, script->scriptPath);
        
        if (luaState[function]) {  // <--- crashes
            luaState[function](entity2);
        }
    }
}

bool hasIntersection(Components::Position& position1, Components::Area2D& area2D,
                     Components::Position& position2, Components::Area2D& area2D2)
{
    if (position1.x < position2.x + area2D2.width && position1.x + area2D.width > position2.x &&
        position1.y < position2.y + area2D2.height && position1.y + area2D.height > position2.y) {
        return true;
    } else {
        return false;
    }
}

template <typename Container, typename T>
bool isIn(const Container& container, const T& value)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

void Physics::updateCollision(Registry& registry, Entity entity, Entity entity2,
                              ScriptSystem& scriptSystem)
{
    auto* position = registry.getComponent<Components::Position>(entity);
    auto* area2D = registry.getComponent<Components::Area2D>(entity);
    if (!position || !area2D) return;

    auto* position2 = registry.getComponent<Components::Position>(entity2);
    auto* area2D2 = registry.getComponent<Components::Area2D>(entity2);
    if (!position2 || !area2D2) return;
    bool intersect = hasIntersection(*position, *area2D, *position2, *area2D2);

    std::vector<Entity> entitiesToAdd;
    std::vector<Entity> entitiesToRemove;

    if (intersect) {
        if (!isIn(area2D->collidedEntities, entity2)) {
            entitiesToAdd.push_back(entity2);
            callFunction(registry, entity, entity2, "onCollide", scriptSystem);
        }
    }

    if (!intersect) {
        if (isIn(area2D->collidedEntities, entity2)) {
            entitiesToRemove.push_back(entity2);
        }
    }

    for (auto entity : entitiesToAdd) {
        area2D->collidedEntities.push_back(entity);
    }

    for (auto entity : entitiesToRemove) {
        area2D->collidedEntities.erase(
            std::remove(area2D->collidedEntities.begin(), area2D->collidedEntities.end(), entity),
            area2D->collidedEntities.end());
    }
}

void Physics::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    std::vector<CollisionInfo> collisions;

    {
        RegistryLock lock(registry);

        for (auto entity : registry.view<Components::Position, Components::Area2D>()) {
            auto* position = registry.getComponent<Components::Position>(entity);
            auto* area2D = registry.getComponent<Components::Area2D>(entity);
            if (!position || !area2D) continue;

            for (auto entity2 : registry.view<Components::Position, Components::Area2D>()) {
                if (entity == entity2) continue;

                auto* position2 = registry.getComponent<Components::Position>(entity2);
                auto* area2D2 = registry.getComponent<Components::Area2D>(entity2);
                if (!position2 || !area2D2) continue;

                bool intersect = hasIntersection(*position, *area2D, *position2, *area2D2);

                if (intersect && !isIn(area2D->collidedEntities, entity2)) {
                    area2D->collidedEntities.push_back(entity2);
                    collisions.push_back({entity, entity2, true});
                }
                else if (!intersect && isIn(area2D->collidedEntities, entity2)) {
                    area2D->collidedEntities.erase(
                        std::remove(area2D->collidedEntities.begin(),
                                    area2D->collidedEntities.end(),
                                    entity2),
                        area2D->collidedEntities.end());
                    collisions.push_back({entity, entity2, false});
                }
            }
        }
    }

    for (const auto& collision : collisions) {
        if (collision.isEntering) {
            callFunction(registry, collision.entity1, collision.entity2, "onCollide", scriptSystem);
        }
    }
}
Physics::~Physics()
{
    cpSpaceFree(_space);
}
