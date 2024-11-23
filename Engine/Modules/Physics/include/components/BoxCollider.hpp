//
// Created by Guillaume Tran on 18/11/2024.
//

#pragma once

#include <functional>

#include "Entity.hpp"
#include "Physics.hpp"

namespace Components {
struct BoxCollider {
    cpBody* body;
    cpShape* shape;
    float width;
    float height;
    std::vector<Entity> collidedEntities;
};
}  // namespace Components
