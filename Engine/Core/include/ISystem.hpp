#pragma once

class ISystem
{
   public:
    virtual ~ISystem() = default;
    virtual void startup() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void shutdown() = 0;
};
