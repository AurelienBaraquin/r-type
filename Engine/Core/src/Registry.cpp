#include "Registry.hpp"

Entity Registry::createEntity() {
    Entity entity = entityManager.createEntity();
    entityMasks[entity] = ComponentMask();
    return entity;
}

void Registry::destroyEntity(Entity entity) {
    entityManager.destroyEntity(entity);
    entityMasks.erase(entity);

    for (auto& [type, pool] : componentPools) {
        pool->remove(entity);
    }
}
