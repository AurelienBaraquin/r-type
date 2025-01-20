#pragma once

namespace Components {
struct Input {
    int inputConfigID;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(inputConfigID);
    }
};
}  // namespace Components

CEREAL_REGISTER_TYPE(ComponentPool<Components::Input>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Input>);
