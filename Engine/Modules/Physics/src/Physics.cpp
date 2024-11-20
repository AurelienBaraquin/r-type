//
// Created by Guillaume Tran on 19/11/2024.
//

#include "Physics.hpp"
#include "Transform.hpp"
#include <typeinfo>
void Physics::Physics::startup()
{
    _space = SpacePtr(cpSpaceNew(), ChipmunkDeleter());
    auto handler = cpSpaceAddCollisionHandler(_space.get(), 0, 0);
    handler->beginFunc = BeginCollision;
    handler->separateFunc = [](cpArbiter *arb, cpSpace *space, void *data) {
        cpShape *a, *b;
        cpArbiterGetShapes(arb, &a, &b);
    };
}

cpBool Physics::BeginCollision(cpArbiter *arb, cpSpace *space, void *data) {
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);
    return true;
}

void Physics::Physics::update(float deltaTime, Registry &registry)
{
    cpSpaceStep(_space.get(), deltaTime);
    for (auto entity : registry.view<Components::BoxCollider, Components::Position>()) //TO DO add rotation
    {
        Components::BoxCollider* boxCollider = registry.getComponent<Components::BoxCollider>(entity);
        auto* position = registry.getComponent<Components::Position>(entity);

        cpBodySetPosition(boxCollider->body.get(), cpVect{(double)position->x, (double)position->y});
    }
}

void Physics::Physics::shutdown()
{
}
