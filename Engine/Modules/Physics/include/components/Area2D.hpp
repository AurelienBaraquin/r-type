//
// Created by Guillaume Tran on 20/11/2024.
//

#pragma once

#include "Entity.hpp"

namespace Components
{
    struct Area2D {
        int width;
        int height;
        Entity firstCollidedEntity;
        std::vector<Entity> collidedEntities;
    };
}  // namespace Components