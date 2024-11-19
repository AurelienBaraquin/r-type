#pragma once

#include "ComponentFactory.hpp"
#include "Event.hpp"
#include "Registry.hpp"
#include "ScriptManager.hpp"

class ISystem
{
   public:
    virtual ~ISystem() = default;
    virtual void startup() = 0;
    virtual void registerScriptBindings(ScriptManager& scriptManager, Registry& registry) = 0;
    virtual void registerComponentFactory(ComponentFactory& componentFactory)
    {
    }
    virtual void update(float deltaTime, Registry& registry) = 0;
    virtual void shutdown() = 0;
};
