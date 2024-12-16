#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>
#include "Loader.hpp"

struct InputConfig {
    std::unordered_map<int, std::string> keyboardBindings;  // Key -> Action
    std::unordered_map<int, std::string> mouseBindings;     // Mouse button -> Action
    std::unordered_map<int, std::string> controllerBindings; // Gamepad button -> Action
};

class InputSystem : public ILoader {
public:
    void load(const nlohmann::json& data) override;
    std::string getPart() override { return "inputConfigs"; }

    void removeInput(int inputConfigID);
    InputConfig& getInput(int inputConfigID);
    std::unordered_map<int, InputConfig>& getAllConfigs() { return configs; }

    void updateInputs(int inputConfigID);
    bool isInputActive(int inputConfigID, const std::string& action, bool allowHold = true);

    const std::unordered_map<std::string, bool>& getCurrentStates() const { return currentStates; }

private:
    int KeyboardKeyFromString(const std::string& keyName);

    std::unordered_map<int, InputConfig> configs;
    std::unordered_map<std::string, bool> currentStates;
    std::unordered_map<std::string, bool> prevStates;
};
