#include "EntityManager.hpp"

Entity EntityManager::createEntity() {
    if (!availableEntities.empty()) {
        Entity id = availableEntities.front();
        availableEntities.pop();
        return id;
    } else {
        return nextEntityId++;
    }
}

void EntityManager::destroyEntity(Entity entity) {
    availableEntities.push(entity);
}
