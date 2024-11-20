#pragma once

#include "ISystem.hpp"
#include "InputSystem.hpp"

class Inputs : public ISystem
{
   public:
    Inputs() = default;
    ~Inputs() override = default;

    void startup() override;
    void update(float deltaTime, Registry& registry) override;
    void shutdown() override;
    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

   private:
    InputSystem _InputSystem;
};
