#pragma once

#include <queue>

#include "Entity.hpp"

class EntityManager
{
   public:
    Entity createEntity();
    void destroyEntity(Entity entity);

    void clear()
    {
        nextEntityId = 0;
        while (!availableEntities.empty()) {
            availableEntities.pop();
        }
    }

   private:
    Entity nextEntityId = 0;
    std::queue<Entity> availableEntities;
};
