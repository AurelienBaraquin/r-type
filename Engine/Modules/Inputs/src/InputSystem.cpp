#include "InputSystem.hpp"

#include <SDL2/SDL.h>

void InputSystem::load(const nlohmann::json& data)
{
    InputConfig _inputConfig;

    for (const auto& inputConfig : data) {
        int inputConfigID = inputConfig["id"].get<int>();
        const auto& inputConfigData = inputConfig["inputConfig"];

        for (const auto& [device, deviceData] : inputConfigData.items()) {
            for (const auto& [str, code] : deviceData.items()) {
                if (device == "id") continue;
                if (device == "keyboard") {
                    SDL_Scancode scancode =
                        SDL_GetScancodeFromName(code.get<std::string>().c_str());
                    if (scancode == SDL_SCANCODE_UNKNOWN)
                        throw std::runtime_error("Unknown scancode: " + code.get<std::string>());
                    _inputConfig.buttons[scancode] = str;
                } else if (device == "mouse") {
                    std::string button = code.get<std::string>();
                    if (button == "LeftButton")
                        _inputConfig.mouseButtons[SDL_BUTTON_LEFT] = str;
                    else if (button == "MiddleButton")
                        _inputConfig.mouseButtons[SDL_BUTTON_MIDDLE] = str;
                    else if (button == "RightButton")
                        _inputConfig.mouseButtons[SDL_BUTTON_RIGHT] = str;
                    else
                        throw std::runtime_error("Unknown mouse button: " + button);
                } else if (device == "controller") {
                    if (code.get<std::string>().find("Stick") != std::string::npos) {
                        if (axisMap.find(code.get<std::string>()) == axisMap.end())
                            throw std::runtime_error("Unknown controller axis: " +
                                                     code.get<std::string>());
                        _inputConfig.controllerAxis[axisMap[code.get<std::string>()]] = str;
                    } else {
                        if (buttonMap.find(code.get<std::string>()) == buttonMap.end())
                            throw std::runtime_error("Unknown controller button: " +
                                                     code.get<std::string>());
                        _inputConfig.controllerButtons[buttonMap[code.get<std::string>()]] = str;
                    }
                } else {
                    throw std::runtime_error("Unknown device: " + device);
                }
            }
        }

        configs[inputConfigID] = _inputConfig;
    }
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
    SDL_PumpEvents();

    for (auto& [_, state] : currentStates) {
        state = false;
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    for (auto& [input, action] : configs[inputConfigID].buttons) {
        if (state[input]) {
            currentStates[action] = true;
        }
    }

    for (auto& [input, action] : configs[inputConfigID].mouseButtons) {
        if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(input)) {
            currentStates[action] = true;
        }
    }
}

bool InputSystem::isInputActive(int inputConfigID, const std::string& action)
{
    updateInputs(inputConfigID);
    return currentStates[action];
}
