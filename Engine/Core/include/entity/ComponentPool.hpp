#pragma once

#include <bitset>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include "Entity.hpp"

constexpr size_t MAX_COMPONENTS = 64;

using ComponentMask = std::bitset<MAX_COMPONENTS>;

class IComponentPool
{
   public:
    virtual ~IComponentPool() = default;
    virtual void remove(Entity entity) = 0;

    template <class Archive>
    void serialize(Archive& archive) {}
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

   private:
    std::unordered_map<Entity, T> components;
};

CEREAL_REGISTER_TYPE(ComponentPool<int>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IComponentPool, ComponentPool<int>);