#pragma once

#include "Registry.hpp"

class EntityBuilder
{
   public:
    EntityBuilder(Entity entity, Registry& registry) : _entity(entity), _registry(registry)
    {
    }

    template <typename T, typename... Args>
    EntityBuilder& addComponent(Args&&... args)
    {
        _registry.addComponent<T>(_entity, std::forward<Args>(args)...);
        return *this;
    }

    EntityBuilder& addTag(Tag tag)
    {
        _registry.addTag(_entity, tag);
        return *this;
    }

    Entity build()
    {
        return _entity;
    }

   private:
    Entity _entity;
    Registry& _registry;
};
