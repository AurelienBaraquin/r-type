#include "Inputs.hpp"

void Inputs::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    _InputSystem.updateInputs();
}
