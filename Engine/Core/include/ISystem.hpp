#pragma once

#include "Async.hpp"
#include "ComponentFactory.hpp"
#include "Event.hpp"
#include "Registry.hpp"
#include "ScriptSystem.hpp"

class NotThreadable
{
};

class ISystem
{
   public:
    virtual ~ISystem() = default;
    virtual void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
    {
    }
    virtual void registerComponentFactory(ComponentFactory& componentFactory)
    {
    }
    virtual void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) = 0;
};
