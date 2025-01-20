#pragma once

#include <bitset>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Entity.hpp"
#include "components/Json.hpp"
#include "components/Script.hpp"
#include "components/Transform.hpp"

constexpr size_t MAX_COMPONENTS = 64;

using ComponentMask = std::bitset<MAX_COMPONENTS>;

class IComponentPool
{
   public:
    virtual ~IComponentPool() = default;
    virtual void remove(Entity entity) = 0;
    virtual std::type_index getTypeIndex() const = 0;

    template <class Archive>
    void serialize(Archive& archive)
    {
    }

    virtual std::unique_ptr<IComponentPool> clone() const = 0;
};

template <typename T>
class ComponentPool : public IComponentPool
{
public:
    void add(Entity entity, T component)
    {
        components[entity] = std::move(component);
    }

    void remove(Entity entity) override
    {
        components.erase(entity);
    }

    T* get(Entity entity)
    {
        auto it = components.find(entity);
        return it != components.end() ? &it->second : nullptr;
    }

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(components);
    }

    std::unique_ptr<IComponentPool> clone() const override
    {
        return std::make_unique<ComponentPool<T>>(*this);
    }

    std::type_index getTypeIndex() const override
    {
        return typeid(T);
    }

private:
    std::unordered_map<Entity, T> components;
};


// Register ComponentPool specializations with Cereal
CEREAL_REGISTER_TYPE(ComponentPool<Components::Json>);
CEREAL_REGISTER_TYPE(ComponentPool<Components::Position>);
CEREAL_REGISTER_TYPE(ComponentPool<Components::Scale>);
CEREAL_REGISTER_TYPE(ComponentPool<Components::Rotation>);
CEREAL_REGISTER_TYPE(ComponentPool<Components::Script>);

// Register polymorphic relationships
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Json>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Position>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Scale>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Rotation>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<Components::Script>);