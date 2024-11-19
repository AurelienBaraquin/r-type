//
// Created by Guillaume Tran on 19/11/2024.
//

#include "Physics.hpp"

void Physics::Physics::startup()
{

}

void Physics::Physics::update(float deltaTime, Registry& registry)
{
    for (auto entity : registry.view<Components::BoxCollider>()) {
        auto& collider = registry.getComponent<Component::BoxCollider>(entity);
    }
}

void Physics::Physics::shutdown()
{

}