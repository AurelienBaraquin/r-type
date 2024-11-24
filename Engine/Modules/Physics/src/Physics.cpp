//
// Created by Guillaume Tran on 19/11/2024.
//

#include "Physics.hpp"

#include <typeinfo>

#include "Area2D.hpp"
#include "Transform.hpp"


void Physics::callCollideFunction(Registry& registry, Entity entity, Entity entity2,
                                  ScriptSystem& _scriptSystem)
{
    auto* script = registry.getComponent<Components::Script>(entity);

    if (script)
    {
        sol::state& luaState = _scriptSystem.getScript(entity, script->scriptPath);
        if (luaState["onCollide"].valid())
        {
            luaState["onCollide"](entity2);
        }
    }
}

bool hasIntersection(Components::Position& position1, Components::Area2D& area2D,
                     Components::Position& position2, Components::Area2D& area2D2)
{
    if (position1.x < position2.x + area2D2.width && position1.x + area2D.width > position2.x &&
        position1.y < position2.y + area2D2.height && position1.y + area2D.height > position2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Physics::updateCollision(Registry& registry, Entity entity, Entity entity2,
                              ScriptSystem& scriptSystem)
{
    auto* position = registry.getComponent<Components::Position>(entity);
    auto* area2D = registry.getComponent<Components::Area2D>(entity);

    auto* position2 = registry.getComponent<Components::Position>(entity2);
    auto* area2D2 = registry.getComponent<Components::Area2D>(entity2);

    if (hasIntersection(*position, *area2D, *position2, *area2D2) &&
        std::find(area2D->collidedEntities.begin(), area2D->collidedEntities.end(),
                  entity2) == area2D->collidedEntities.end())
    {
        area2D->collidedEntities.push_back(entity2);
        area2D2->collidedEntities.push_back(entity);
        callCollideFunction(registry, entity, entity2, scriptSystem);
        callCollideFunction(registry, entity2, entity, scriptSystem);
    }
    if (hasIntersection(*position, *area2D, *position2, *area2D2) &&
        std::find(area2D->collidedEntities.begin(), area2D->collidedEntities.end(),
                  entity2) != area2D->collidedEntities.end())
    {
        area2D->collidedEntities.erase(std::remove(area2D->collidedEntities.begin(),
                                                   area2D->collidedEntities.end(), entity2),
                                       area2D->collidedEntities.end());
        area2D2->collidedEntities.erase(
                std::remove(area2D2->collidedEntities.begin(), area2D2->collidedEntities.end(),
                            entity),
                area2D2->collidedEntities.end());
    }
}

void Physics::Physics::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    for (auto entity : registry.view<Components::Position, Components::Area2D>())
    {
        auto* position = registry.getComponent<Components::Position>(entity);
        auto* area2D = registry.getComponent<Components::Area2D>(entity);

        for (auto entity2 : registry.view<Components::Position, Components::Area2D>())
        {
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
