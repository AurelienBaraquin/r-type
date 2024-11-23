#include "Registry.hpp"

Entity Registry::createEntity(std::vector<Tag> tags)
{
    Entity entity = entityManager.createEntity();
    entityMasks[entity] = ComponentMask();

    for (const auto& tag : tags) {
        _tags[tag].push_back(entity);
    }

    return entity;
}

void Registry::destroyEntity(Entity entity)
{
    entityManager.destroyEntity(entity);
    entityMasks.erase(entity);

    for (auto& [tag, entities] : _tags) {
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    }

    for (auto& [type, pool] : componentPools) {
        pool->remove(entity);
    }
}
