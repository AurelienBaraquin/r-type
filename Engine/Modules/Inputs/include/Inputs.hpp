#pragma once

#include <unordered_map>
#include "ISystem.hpp"
#include "InputSystem.hpp"
#include "Loader.hpp"
#include "Input.hpp"

class Inputs : public ISystem, public ILoader, public NotThreadable {
public:
    Inputs();
    ~Inputs() override = default;

    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;
    void registerScriptBindings(ScriptSystem& scriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

    // ILoader interface
    void load(const nlohmann::json& data) override {}
    std::vector<ILoader*> getLoaders() override { return {dynamic_cast<ILoader*>(&_InputSystem)}; }
    std::string getPart() override { return "inputs"; }

private:
    InputSystem _InputSystem;
};
