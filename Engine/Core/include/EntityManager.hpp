#pragma once

#include "Entity.hpp"
#include <queue>

class EntityManager {
public:
    Entity createEntity() {
        if (!availableEntities.empty()) {
            Entity id = availableEntities.front();
            availableEntities.pop();
            return id;
        } else {
            return nextEntityId++;
        }
    }

    void destroyEntity(Entity entity) {
        availableEntities.push(entity);
    }

private:
    Entity nextEntityId = 0;
    std::queue<Entity> availableEntities;
};
