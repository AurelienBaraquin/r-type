#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/types/queue.hpp>
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
void load(const EntityManager& entityManager)
{
    this->availableEntities = entityManager.getAvailableEntities();
    this->nextEntityId = entityManager.getNextEntityId();
}

std::queue<Entity> getAvailableEntities() const
{
    return availableEntities;
}

int getNextEntityId() const
{
    return nextEntityId;
}

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(nextEntityId, availableEntities);
    }

   private:
    Entity nextEntityId = 0;
    std::queue<Entity> availableEntities;
};