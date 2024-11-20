#pragma once

#include "ComponentFactory.hpp"
#include "Event.hpp"
#include "Registry.hpp"
#include "ScriptSystem.hpp"

class ISystem
{
   public:
    virtual ~ISystem() = default;
    virtual void startup() = 0;
    virtual void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
    {
    }
    virtual void registerComponentFactory(ComponentFactory& componentFactory)
    {
    }
    virtual void update(float deltaTime, Registry& registry) = 0;
    virtual void shutdown() = 0;
};
