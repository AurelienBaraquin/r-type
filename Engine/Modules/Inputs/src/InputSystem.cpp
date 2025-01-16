#include "InputSystem.hpp"

void InputSystem::load(const nlohmann::json& data)
{
    for (const auto& inputConfig : data) {
        int inputConfigID = inputConfig["id"].get<int>();
        const auto& inputConfigData = inputConfig["inputConfig"];

        InputConfig config;

        for (const auto& [device, bindings] : inputConfigData.items()) {
            for (const auto& [action, key] : bindings.items()) {
                if (device == "keyboard") {
                    int keyCode = KeyboardKeyFromString(key.get<std::string>());
                    if (keyCode == -1) {
                        throw std::runtime_error("Invalid key name: " + key.get<std::string>());
                    }
                    config.keyboardBindings[keyCode] = action;
                } else if (device == "mouse") {
                    // int buttonCode = std::stoi(key.get<std::string>());
                    // config.mouseBindings[buttonCode] = action;
                } else if (device == "controller") {
                    // int buttonCode = std::stoi(key.get<std::string>());
                    // config.controllerBindings[buttonCode] = action;
                }
            }
        }

        configs[inputConfigID] = config;
    }
}

void InputSystem::applyExternalInputStates(int inputConfigID, const std::vector<std::string>& states)
{
    for (auto& [action, state] : currentStates) {
        state = false;
    }

    for (const auto &action : states) {
        currentStates[action] = true;
    }
}

void InputSystem::emptyInputStates()
{
    for (auto& [action, state] : currentStates) {
        state = false;
    }
}

int InputSystem::KeyboardKeyFromString(const std::string& keyName)
{
    const static std::unordered_map<std::string, int> keyMap = {{"A", KEY_A},
                                                                {"B", KEY_B},
                                                                {"C", KEY_C},
                                                                {"D", KEY_D},
                                                                {"E", KEY_E},
                                                                {"F", KEY_F},
                                                                {"G", KEY_G},
                                                                {"H", KEY_H},
                                                                {"I", KEY_I},
                                                                {"J", KEY_J},
                                                                {"K", KEY_K},
                                                                {"L", KEY_L},
                                                                {"M", KEY_M},
                                                                {"N", KEY_N},
                                                                {"O", KEY_O},
                                                                {"P", KEY_P},
                                                                {"Q", KEY_Q},
                                                                {"R", KEY_R},
                                                                {"T", KEY_T},
                                                                {"U", KEY_U},
                                                                {"V", KEY_V},
                                                                {"X", KEY_X},
                                                                {"Y", KEY_Y},
                                                                {"Z", KEY_Z},
                                                                {"W", KEY_W},
                                                                {"S", KEY_S},
                                                                {"SPACE", KEY_SPACE},
                                                                {"ESCAPE", KEY_ESCAPE},
                                                                {"UP", KEY_UP},
                                                                {"DOWN", KEY_DOWN},
                                                                {"LEFT", KEY_LEFT},
                                                                {"RIGHT", KEY_RIGHT},
                                                                {"ENTER", KEY_ENTER},
                                                                {"BACKSPACE", KEY_BACKSPACE},
                                                                {"TAB", KEY_TAB},
                                                                {"SHIFT", KEY_LEFT_SHIFT},
                                                                {"CTRL", KEY_LEFT_CONTROL},
                                                                {"ALT", KEY_LEFT_ALT},
                                                                {"CAPSLOCK", KEY_CAPS_LOCK},
                                                                {"NUMLOCK", KEY_NUM_LOCK},
                                                                {"F1", KEY_F1},
                                                                {"F2", KEY_F2},
                                                                {"F3", KEY_F3},
                                                                {"F4", KEY_F4},
                                                                {"F5", KEY_F5},
                                                                {"F6", KEY_F6},
                                                                {"F7", KEY_F7},
                                                                {"F8", KEY_F8},
                                                                {"F9", KEY_F9},
                                                                {"F10", KEY_F10},
                                                                {"F11", KEY_F11},
                                                                {"F12", KEY_F12}};

    auto it = keyMap.find(keyName);
    return (it != keyMap.end()) ? it->second : -1;
}

void InputSystem::removeInput(int inputConfigID)
{
    configs.erase(inputConfigID);
}

InputConfig& InputSystem::getInput(int inputConfigID)
{
    return configs[inputConfigID];
}

void InputSystem::updateInputs(int inputConfigID)
{
    auto& config = configs[inputConfigID];

    for (auto& [action, state] : currentStates) {
        state = false;
    }

    for (const auto& [key, action] : config.keyboardBindings) {
        if (IsKeyDown(key)) {
            currentStates[action] = true;
        }
    }

    for (const auto& [button, action] : config.mouseBindings) {
        if (IsMouseButtonDown(button)) {
            currentStates[action] = true;
        }
    }

    for (const auto& [button, action] : config.controllerBindings) {
        if (IsGamepadButtonDown(0, button)) {
            currentStates[action] = true;
        }
    }
}

bool InputSystem::isInputActive(int inputConfigID, const std::string& action, bool allowHold)
{
    bool isActive = currentStates[action];

    if (!allowHold) {
        bool wasActive = prevStates[action];
        prevStates[action] = isActive;
        return isActive && !wasActive;
    }

    return isActive;
}
