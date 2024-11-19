#pragma once

#include "ComponentPool.hpp"
#include "EntityManager.hpp"
#include <vector>
#include <algorithm>

class Registry
{
   public:
    Entity createEntity(std::vector<Tag> tags = {});
    void destroyEntity(Entity entity);

    std::vector<Entity> getEntitiesByTag(Tag tag)
    {
        return _tags[tag];
    }

    void addTag(Entity entity, Tag tag)
    {
        _tags[tag].push_back(entity);
    }

    void removeTag(Entity entity, Tag tag)
    {
        auto& entities = _tags[tag];
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    }

    void removeAllTags(Entity entity)
    {
        for (auto& [tag, entities] : _tags)
        {
            entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
        }
    }

    void removeEntityByTag(Tag tag)
    {
        for (auto entity : _tags[tag])
        {
            destroyEntity(entity);
        }
    }

    template <typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args)
    {
        getOrCreatePool<T>()->add(entity, T{std::forward<Args>(args)...});
        entityMasks[entity].set(getComponentTypeId<T>());
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        getPool<T>()->remove(entity);
        entityMasks[entity].reset(getComponentTypeId<T>());
    }

    template <typename T>
    T* getComponent(Entity entity)
    {
        auto pool = getPool<T>();
        return pool ? pool->get(entity) : nullptr;
    }

    template <typename... Components>
    std::vector<Entity> view()
    {
        std::vector<Entity> result;
        for (const auto& [entity, mask] : entityMasks)
        {
            if ((mask & componentMask<Components...>()) == componentMask<Components...>())
            {
                result.push_back(entity);
            }
        }
        return result;
    }

    void clear()
    {
        entityManager.clear();
        _tags.clear();
        entityMasks.clear();
        componentPools.clear();
    }

   private:
    EntityManager entityManager;
    std::unordered_map<Tag, std::vector<Entity>> _tags;
    std::unordered_map<Entity, ComponentMask> entityMasks;
    std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> componentPools;

    template <typename T>
    ComponentPool<T>* getPool()
    {
        auto it = componentPools.find(typeid(T));
        return it != componentPools.end() ? static_cast<ComponentPool<T>*>(it->second.get())
                                          : nullptr;
    }

    template <typename T>
    ComponentPool<T>* getOrCreatePool()
    {
        auto it = componentPools.find(typeid(T));
        if (it == componentPools.end())
        {
            auto pool = std::make_unique<ComponentPool<T>>();
            componentPools[typeid(T)] = std::move(pool);
        }
        return static_cast<ComponentPool<T>*>(componentPools[typeid(T)].get());
    }

    template <typename T>
    size_t getComponentTypeId()
    {
        static size_t id = nextComponentTypeId++;
        return id;
    }

    template <typename... Components>
    ComponentMask componentMask()
    {
        ComponentMask mask;
        (mask.set(getComponentTypeId<Components>()), ...);
        return mask;
    }

    inline static size_t nextComponentTypeId = 0;
};
