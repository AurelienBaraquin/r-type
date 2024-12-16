#include "Inputs.hpp"
#include "Sharable.hpp"

Inputs::Inputs() {
    Sharable::getInstance().registerSharedVariable("InputStates", [this]() -> Sharable::SharedData {
        std::vector<std::string> inputStates;

        for (const auto& [name, state] : _InputSystem.getCurrentStates())
            if (state)
                inputStates.push_back(name);
        
        return inputStates;
    });
}

void Inputs::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) {
    for (auto& [id, _] : _InputSystem.getAllConfigs()) {
        _InputSystem.updateInputs(id);
    }
}
