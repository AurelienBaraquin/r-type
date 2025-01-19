#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include "ComponentPool.hpp"  // Include ComponentPool

namespace Components {
struct Sprite {
    int spriteID;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(spriteID);
    }
};
}  // namespace Components

struct BrutSprite {
    int textureID;
    int width;
    int height;
    int originX;
    int originY;
};

CEREAL_REGISTER_TYPE(ComponentPool<Components::Sprite>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Sprite>);