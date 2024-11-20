#pragma once

#include "Input.hpp"
#include "ISystem.hpp"
#include "Loader.hpp"

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
    std::unordered_map<std::string, bool> buttons;
    std::unordered_map<std::string, float> axes;
};
