#pragma once

#include "ISystem.hpp"
#include "InputSystem.hpp"
#include "Loader.hpp"

class Inputs : public ISystem, public ILoader
{
   public:
    Inputs() = default;
    ~Inputs() override = default;

    void startup() override;
    void update(float deltaTime, Registry& registry) override;
    void shutdown() override;
    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

    void load(const std::string& filePath) override
    {
        _InputSystem.load(filePath);
    }

   private:
    InputSystem _InputSystem;
};
