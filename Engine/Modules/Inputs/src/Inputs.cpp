#include "Inputs.hpp"
#include "Sharable.hpp"

void Inputs::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) {
#ifdef CLIENT
    for (auto& [id, _] : _InputSystem.getAllConfigs()) {
        _InputSystem.updateInputs(id);
    }

    std::vector<std::string> inputStates;
    for (const auto& [name, state] : _InputSystem.getCurrentStates()) {
        if (state) {
            inputStates.push_back(name);
        }
    }
    Sharable::getInstance().setSharedVariable("InputStates", inputStates);
#endif

#ifdef SERVER
    _InputSystem.emptyInputStates();

    auto data = Sharable::getInstance().getSharedVariable("InputLoads");
    Sharable::getInstance().setSharedVariable("InputLoads", std::vector<std::string>{});

    std::vector<std::string> dataStr;
    if (data.has_value()) {
        if (auto inputVec = std::get_if<std::vector<std::string>>(&(*data))) {
            dataStr = *inputVec;
        }
    }
    _InputSystem.applyExternalInputStates(0, dataStr);
#endif
}
