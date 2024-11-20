//
// Created by Guillaume Tran on 19/11/2024.
//

#include "Physics.hpp"
#include "Transform.hpp"
#include "Area2D.hpp"
#include <typeinfo>

void Physics::Physics::startup()
{
//    _space = cpSpaceNew(); //TODO destroy space
//    cpCollisionHandler *handler = cpSpaceAddDefaultCollisionHandler(_space);
//    handler->beginFunc = BeginCollision;
}

//cpBool Physics::BeginCollision(cpArbiter *arb, cpSpace *space, void *data) {
//    cpShape *a, *b;
//    cpArbiterGetShapes(arb, &a, &b);
//    std::cout << "Collision between " << typeid(a).name() << " and " << typeid(b).name() << std::endl;
//    return true;
//}

void Physics::callCollideFunction(Registry& registry, Entity entity, Entity entity2, ScriptSystem& _scriptSystem)
{
    auto* script = registry.getComponent<Components::Script>(entity);

    if (script) {
        sol::state& luaState = _scriptSystem.getScript(script->scriptPath);
        if (luaState["onCollide"].valid())
        {
            luaState["onCollide"](entity2);
        }
    }
}

void Physics::Physics::update(float deltaTime, Registry &registry, ScriptSystem& scriptSystem)
{
    for (auto entity : registry.view<Components::Position, Components::Area2D>())
    {
        auto *position = registry.getComponent<Components::Position>(entity);
        auto *area2D = registry.getComponent<Components::Area2D>(entity);

        for (auto entity2 : registry.view<Components::Position, Components::Area2D>())
        {
            if (entity == entity2)
                continue;
            auto *position2 = registry.getComponent<Components::Position>(entity2);
            auto *area2D2 = registry.getComponent<Components::Area2D>(entity2);

            SDL_Rect rect1 = {position->x, position->y, area2D->width, area2D->height};
            SDL_Rect rect2 = {position2->x, position2->y, area2D2->width, area2D2->height};

            if (SDL_HasIntersection(&rect1, &rect2) && std::find(area2D->collidedEntities.begin(), area2D->collidedEntities.end(), entity2) == area2D->collidedEntities.end()) {
                area2D->collidedEntities.push_back(entity2);
                area2D2->collidedEntities.push_back(entity);
                callCollideFunction(registry, entity, entity2, scriptSystem);
                callCollideFunction(registry, entity2, entity, scriptSystem);

            }
            if (!SDL_HasIntersection(&rect1, &rect2) && std::find(area2D->collidedEntities.begin(), area2D->collidedEntities.end(), entity2) != area2D->collidedEntities.end()) {
                area2D->collidedEntities.erase(std::remove(area2D->collidedEntities.begin(), area2D->collidedEntities.end(), entity2), area2D->collidedEntities.end());
                area2D2->collidedEntities.erase(std::remove(area2D2->collidedEntities.begin(), area2D2->collidedEntities.end(), entity), area2D2->collidedEntities.end());
            }
        }
    }
//    cpSpaceStep(_space, deltaTime);
//    for (auto entity : registry.view<Components::BoxCollider, Components::Position>()) //TO DO add rotation
//    {
//        Components::BoxCollider *boxCollider = registry.getComponent<Components::BoxCollider>(entity);
//        auto *position = registry.getComponent<Components::Position>(entity);
//        cpBodySetPosition(boxCollider->body, cpv(position->x, position->y));
//        std::cout << cpBodyGetPosition(boxCollider->body).x << " " << cpBodyGetPosition(boxCollider->body).y << std::endl;
//    }
}

void Physics::Physics::shutdown()
{
    cpSpaceFree(_space);
}
