#include "Inputs.hpp"

void Inputs::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) {
    for (auto& [id, _] : _InputSystem.getAllConfigs()) {
        _InputSystem.updateInputs(id);
    }
}
