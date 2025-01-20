//
// Created by Guillaume Tran on 20/11/2024.
//

#pragma once

#include <cereal/types/vector.hpp>
#include <vector>

#include "ComponentPool.hpp"
#include "Entity.hpp"

namespace Components {
struct Area2D {
    int width;
    int height;
    Entity firstCollidedEntity;
    std::vector<Entity> collidedEntities;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(width, height, firstCollidedEntity, collidedEntities);
    }
};
}  // namespace Components

CEREAL_REGISTER_TYPE(ComponentPool<Components::Area2D>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Area2D>);
