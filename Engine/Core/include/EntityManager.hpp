#pragma once

#include "Entity.hpp"
#include <queue>

class EntityManager {
public:
    Entity createEntity();
    void destroyEntity(Entity entity);

private:
    Entity nextEntityId = 0;
    std::queue<Entity> availableEntities;
};
