//
// Created by Guillaume Tran on 19/11/2024.
//

#include "Physics.hpp"

#include <typeinfo>

#include "Area2D.hpp"
#include "Transform.hpp"

void Physics::callFunction(Registry& registry, Entity entity, Entity entity2, std::string function,
                           ScriptSystem& _scriptSystem)
{
    auto* script = registry.getComponent<Components::Script>(entity);

    if (script) {
        sol::state& luaState = _scriptSystem.getScript(entity, script->scriptPath);
        if (luaState[function].valid()) {
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

    if (intersect) {
        if (!isIn(area2D->collidedEntities, entity2)) {
            area2D->collidedEntities.push_back(entity2);
            area2D2->collidedEntities.push_back(entity);
            callFunction(registry, entity, entity2, "onCollide", scriptSystem);
        }
    }

    if (!intersect) {
        if (isIn(area2D->collidedEntities, entity2)) {
            area2D->collidedEntities.erase(std::remove(area2D->collidedEntities.begin(),
                                                       area2D->collidedEntities.end(), entity2),
                                           area2D->collidedEntities.end());
            area2D2->collidedEntities.erase(std::remove(area2D2->collidedEntities.begin(),
                                                        area2D2->collidedEntities.end(), entity),
                                            area2D2->collidedEntities.end());

            callFunction(registry, entity, entity2, "onEndCollide", scriptSystem);
        }
    }
}

void Physics::Physics::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    std::cout << "------" << std::endl;
    for (auto entity : registry.view<Components::Position, Components::Area2D>()) {
        auto* position = registry.getComponent<Components::Position>(entity);
        auto* area2D = registry.getComponent<Components::Area2D>(entity);

        for (auto entity2 : registry.view<Components::Position, Components::Area2D>()) {
            std::cout << entity << " " << entity2 << std::endl;
            if (entity == entity2) continue;
            updateCollision(registry, entity, entity2, scriptSystem);
        }
    }

    //    cpSpaceStep(_space, deltaTime);
    //    for (auto entity : registry.view<Components::BoxCollider, Components::Position>()) //TO DO
    //    add rotation
    //    {
    //        Components::BoxCollider *boxCollider =
    //        registry.getComponent<Components::BoxCollider>(entity); auto *position =
    //        registry.getComponent<Components::Position>(entity);
    //        cpBodySetPosition(boxCollider->body, cpv(position->x, position->y));
    //        std::cout << cpBodyGetPosition(boxCollider->body).x << " " <<
    //        cpBodyGetPosition(boxCollider->body).y << std::endl;
    //    }
}

Physics::~Physics()
{
    cpSpaceFree(_space);
}
