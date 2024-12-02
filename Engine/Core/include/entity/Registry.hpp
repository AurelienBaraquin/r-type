#pragma once

#include <algorithm>
#include <mutex>
#include <shared_mutex>
#include <vector>

#include "ComponentPool.hpp"
#include "EntityManager.hpp"

class Registry
{
   public:
    Entity createEntity(std::vector<Tag> tags = {});
    void destroyEntity(Entity entity);

    void lock()
    {
        mutex.lock();
        inRegionLock = true;
    }

    void unlock()
    {
        mutex.unlock();
        inRegionLock = false;
    }

    std::vector<Entity> getEntitiesByTag(Tag tag) const
    {
        if (!inRegionLock) {
            std::shared_lock lock(mutex);
            auto it = _tags.find(tag);
            if (it != _tags.end()) {
                return it->second;
            }
            return {};
        } else {
            auto it = _tags.find(tag);
            if (it != _tags.end()) {
                return it->second;
            }
            return {};
        }
    }

    bool hasTag(Entity entity, Tag tag) const
    {
        if (!inRegionLock) {
            std::shared_lock lock(mutex);
            auto it = _tags.find(tag);
            return it != _tags.end() &&
                   std::find(it->second.begin(), it->second.end(), entity) != it->second.end();
        } else {
            auto it = _tags.find(tag);
            return it != _tags.end() &&
                   std::find(it->second.begin(), it->second.end(), entity) != it->second.end();
        }
    }

    void addTag(Entity entity, Tag tag)
    {
        if (!inRegionLock) {
            std::unique_lock lock(mutex);
            _tags[tag].push_back(entity);
        } else {
            _tags[tag].push_back(entity);
        }
    }

    void removeTag(Entity entity, Tag tag)
    {
        if (!inRegionLock) {
            std::unique_lock lock(mutex);
            auto it = _tags.find(tag);
            if (it != _tags.end()) {
                auto& entities = it->second;
                entities.erase(std::remove(entities.begin(), entities.end(), entity),
                               entities.end());
            }
        } else {
            auto it = _tags.find(tag);
            if (it != _tags.end()) {
                auto& entities = it->second;
                entities.erase(std::remove(entities.begin(), entities.end(), entity),
                               entities.end());
            }
        }
    }

    void removeAllTags(Entity entity)
    {
        if (!inRegionLock) {
            std::unique_lock lock(mutex);
            for (auto& [tag, entities] : _tags) {
                entities.erase(std::remove(entities.begin(), entities.end(), entity),
                               entities.end());
            }
        } else {
            for (auto& [tag, entities] : _tags) {
                entities.erase(std::remove(entities.begin(), entities.end(), entity),
                               entities.end());
            }
        }
    }

    void removeEntityByTag(Tag tag)
    {
        if (!inRegionLock) {
            std::unique_lock lock(mutex);
            auto it = _tags.find(tag);
            if (it != _tags.end()) {
                for (auto entity : it->second) {
                    destroyEntity(entity);
                }
            }
        } else {
            auto it = _tags.find(tag);
            if (it != _tags.end()) {
                for (auto entity : it->second) {
                    destroyEntity(entity);
                }
            }
        }
    }

    template <typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args)
    {
        if (!inRegionLock) {
            std::unique_lock lock(mutex);
            getOrCreatePool<T>()->add(entity, T{std::forward<Args>(args)...});
            entityMasks[entity].set(getComponentTypeId<T>());
        } else {
            getOrCreatePool<T>()->add(entity, T{std::forward<Args>(args)...});
            entityMasks[entity].set(getComponentTypeId<T>());
        }
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        if (!inRegionLock) {
            std::unique_lock lock(mutex);
            getPool<T>()->remove(entity);
            entityMasks[entity].reset(getComponentTypeId<T>());
        } else {
            getPool<T>()->remove(entity);
            entityMasks[entity].reset(getComponentTypeId<T>());
        }
    }

    template <typename T>
    T* getComponent(Entity entity) const
    {
        if (!inRegionLock) {
            std::shared_lock lock(mutex);
            auto pool = getPool<T>();
            return pool ? pool->get(entity) : nullptr;
        } else {
            auto pool = getPool<T>();
            return pool ? pool->get(entity) : nullptr;
        }
    }

    template <typename T>
    bool hasComponent(Entity entity) const
    {
        if (!inRegionLock) {
            std::shared_lock lock(mutex);
            return entityMasks.count(entity) &&
                   entityMasks.at(entity).test(getComponentTypeId<T>());
        } else {
            return entityMasks.count(entity) &&
                   entityMasks.at(entity).test(getComponentTypeId<T>());
        }
    }

    template <typename... Components>
    std::vector<Entity> view() const
    {
        if (!inRegionLock) {
            std::shared_lock lock(mutex);
            std::vector<Entity> result;
            for (const auto& [entity, mask] : entityMasks) {
                if ((mask & componentMask<Components...>()) == componentMask<Components...>()) {
                    result.push_back(entity);
                }
            }
            return result;
        } else {
            std::vector<Entity> result;
            for (const auto& [entity, mask] : entityMasks) {
                if ((mask & componentMask<Components...>()) == componentMask<Components...>()) {
                    result.push_back(entity);
                }
            }
            return result;
        }
    }

    template <typename... Components>
    std::vector<Entity> view(const std::vector<Entity>& entities) const
    {
        if (!inRegionLock) {
            std::shared_lock lock(mutex);
            std::vector<Entity> result;
            for (const auto& entity : entities) {
                if ((entityMasks.at(entity) & componentMask<Components...>()) ==
                    componentMask<Components...>()) {
                    result.push_back(entity);
                }
            }
            return result;
        } else {
            std::vector<Entity> result;
            for (const auto& entity : entities) {
                if ((entityMasks.at(entity) & componentMask<Components...>()) ==
                    componentMask<Components...>()) {
                    result.push_back(entity);
                }
            }
            return result;
        }
    }

    void clear()
    {
        if (!inRegionLock) {
            std::unique_lock lock(mutex);
            entityManager.clear();
            _tags.clear();
            entityMasks.clear();
            componentPools.clear();
        } else {
            entityManager.clear();
            _tags.clear();
            entityMasks.clear();
            componentPools.clear();
        }
    }

   private:
    EntityManager entityManager;
    std::unordered_map<Tag, std::vector<Entity>> _tags;
    std::unordered_map<Entity, ComponentMask> entityMasks;
    std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> componentPools;

    mutable bool inRegionLock = false;

    mutable std::shared_mutex mutex;

    template <typename T>
    ComponentPool<T>* getPool() const
    {
        auto it = componentPools.find(typeid(T));
        return it != componentPools.end() ? static_cast<ComponentPool<T>*>(it->second.get())
                                          : nullptr;
    }

    template <typename T>
    ComponentPool<T>* getOrCreatePool()
    {
        auto it = componentPools.find(typeid(T));
        if (it == componentPools.end()) {
            auto pool = std::make_unique<ComponentPool<T>>();
            componentPools[typeid(T)] = std::move(pool);
        }
        return static_cast<ComponentPool<T>*>(componentPools[typeid(T)].get());
    }

    template <typename T>
    size_t getComponentTypeId() const
    {
        static size_t id = nextComponentTypeId++;
        return id;
    }

    template <typename... Components>
    ComponentMask componentMask() const
    {
        ComponentMask mask;
        (mask.set(getComponentTypeId<Components>()), ...);
        return mask;
    }

    inline static std::size_t nextComponentTypeId = 0;
};

class RegistryLock
{
   public:
    explicit RegistryLock(Registry& registry) : registry(registry)
    {
        registry.lock();
    }

    ~RegistryLock()
    {
        registry.unlock();
    }

   private:
    Registry& registry;
};
