#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include "ComponentPool.hpp"

namespace Components {
struct Animation {
    int animationID;
    int currentFrame;
    float elapsedTime;
    bool loop;
    bool playing;

    int baseAnimationID = animationID;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(animationID, currentFrame, elapsedTime, loop, playing, baseAnimationID);
    }
};
}  // namespace Components

CEREAL_REGISTER_TYPE(ComponentPool<Components::Animation>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Animation>);