//
// Created by Guillaume Tran on 19/11/2024.
//

#include "Physics.hpp"
#include <chipmunk/chipmunk.h>

void Physics::Physics::startup()
{

}

bool checkCollisionAABB(Components::BoxCollider *a, Components::BoxCollider *b)
{
    return (a->x < b->x + b->width &&
            a->x + a->width > b->x &&
            a->y < b->y + b->height &&
            a->y + a->height > b->y);
}

void Physics::Physics::update(float deltaTime, Registry &registry)
{
//    for (auto entity : registry.view<Components::BoxCollider>()) {
//        Components::BoxCollider *collider = registry.getComponent<Components::BoxCollider>(entity);
//        for (auto entity2 : registry.view<Components::BoxCollider>()) {
//            if (entity == entity2)
//                continue;
//            Components::BoxCollider *collider2 = registry.getComponent<Components::BoxCollider>(entity2);
//
//
//            if (checkCollisionAABB(collider, collider2)) {
//                collider->collidedEntities.push_back(entity2);
//            }
//        }
//    }
}

void Physics::Physics::shutdown()
{
}
