#pragma once

#include "Registry.hpp"

class ISystem
{
   public:
    virtual ~ISystem() = default;
    virtual void startup() = 0;
    virtual void update(float deltaTime, Registry& registry) = 0;
    virtual void shutdown() = 0;
};
