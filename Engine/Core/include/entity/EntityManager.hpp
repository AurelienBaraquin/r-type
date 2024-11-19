#pragma once

#include <queue>

#include "Entity.hpp"

class EntityManager
{
   public:
    Entity createEntity();
    void destroyEntity(Entity entity);

   private:
    Entity nextEntityId = 0;
    std::queue<Entity> availableEntities;
};
