#include "InputSystem.hpp"

#include <SDL2/SDL.h>

void InputSystem::load(const nlohmann::json& data)
{
    InputConfig _inputConfig;

    for (const auto& inputConfig : data) {
        int inputConfigID = inputConfig["id"].get<int>();
        const auto& inputConfigData = inputConfig["inputConfig"];

        for (const auto& [device, deviceData] : inputConfigData.items()) {
            auto it = deviceLoaders.find(device);
            if (it != deviceLoaders.end()) {
                it->second(deviceData, _inputConfig);
            } else {
                throw std::runtime_error("Unknown device: " + device);
            }
        }

        configs[inputConfigID] = _inputConfig;
    }
}

void InputSystem::loadKeyboardConfig(const nlohmann::json& deviceData, InputConfig& _inputConfig)
{
    for (const auto& [str, code] : deviceData.items()) {
        SDL_Scancode scancode = SDL_GetScancodeFromName(code.get<std::string>().c_str());
        if (scancode == SDL_SCANCODE_UNKNOWN)
            throw std::runtime_error("Unknown scancode: " + code.get<std::string>());
        _inputConfig.buttons[scancode] = str;
    }
}

void InputSystem::loadMouseConfig(const nlohmann::json& deviceData, InputConfig& _inputConfig)
{
    for (const auto& [str, code] : deviceData.items()) {
        std::string button = code.get<std::string>();
        if (button == "LeftButton")
            _inputConfig.mouseButtons[SDL_BUTTON_LEFT] = str;
        else if (button == "MiddleButton")
            _inputConfig.mouseButtons[SDL_BUTTON_MIDDLE] = str;
        else if (button == "RightButton")
            _inputConfig.mouseButtons[SDL_BUTTON_RIGHT] = str;
        else
            throw std::runtime_error("Unknown mouse button: " + button);
    }
}

void InputSystem::loadControllerConfig(const nlohmann::json& deviceData, InputConfig& _inputConfig)
{
    for (const auto& [str, code] : deviceData.items()) {
        if (code.get<std::string>().find("Stick") != std::string::npos) {
            if (axisMap.find(code.get<std::string>()) == axisMap.end())
                throw std::runtime_error("Unknown controller axis: " + code.get<std::string>());
            _inputConfig.controllerAxis[axisMap[code.get<std::string>()]] = str;
        } else {
            if (buttonMap.find(code.get<std::string>()) == buttonMap.end())
                throw std::runtime_error("Unknown controller button: " + code.get<std::string>());
            _inputConfig.controllerButtons[buttonMap[code.get<std::string>()]] = str;
        }
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

SDL_GameController *findController() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            return SDL_GameControllerOpen(i);
        }
    }

    return nullptr;
}

void InputSystem::updateInputs(int inputConfigID)
{
    // Réinitialiser les états actuels
    for (auto& [_, state] : currentStates) {
        state = false;
    }

    // Récupération de l'état du clavier
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    for (auto& [input, action] : configs[inputConfigID].buttons) {
        if (keyboardState[input]) {
            currentStates[action] = true;
        }
    }

    // Récupération de l'état de la souris
    int x, y;
    Uint32 mouseButtonsState = SDL_GetMouseState(&x, &y);
    for (auto& [mouseButton, action] : configs[inputConfigID].mouseButtons) {
        if (mouseButtonsState & SDL_BUTTON(mouseButton)) {
            currentStates[action] = true;
        }
    }

    static auto controllerInited = false;

    if (!controllerInited) {
        controller = findController();
        controllerInited = true;
    }
    if (controller) {
        // Gestion des boutons de la manette
        for (auto& [button, action] : configs[inputConfigID].controllerButtons) {
            if (SDL_GameControllerGetButton(controller, button)) {
                currentStates[action] = true;
            }
        }

        // Gestion des axes de la manette
        // Définition d’une deadzone : en dessous de cette valeur absolue, on considère l’axe comme inactif.
        const Sint16 DEADZONE = 8000;

        for (auto& [axis, action] : configs[inputConfigID].controllerAxis) {
            SDL_GameControllerAxis sdlAxis;
            bool checkPositive = false;
            bool checkNegative = false;

            switch (axis) {
                case CONTROLLER_AXIS::LEFT_STICK_X_POSITIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_LEFTX;
                    checkPositive = true;
                    break;
                case CONTROLLER_AXIS::LEFT_STICK_X_NEGATIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_LEFTX;
                    checkNegative = true;
                    break;
                case CONTROLLER_AXIS::LEFT_STICK_Y_POSITIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_LEFTY;
                    checkPositive = true;
                    break;
                case CONTROLLER_AXIS::LEFT_STICK_Y_NEGATIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_LEFTY;
                    checkNegative = true;
                    break;
                case CONTROLLER_AXIS::RIGHT_STICK_X_POSITIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_RIGHTX;
                    checkPositive = true;
                    break;
                case CONTROLLER_AXIS::RIGHT_STICK_X_NEGATIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_RIGHTX;
                    checkNegative = true;
                    break;
                case CONTROLLER_AXIS::RIGHT_STICK_Y_POSITIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_RIGHTY;
                    checkPositive = true;
                    break;
                case CONTROLLER_AXIS::RIGHT_STICK_Y_NEGATIVE:
                    sdlAxis = SDL_CONTROLLER_AXIS_RIGHTY;
                    checkNegative = true;
                    break;
            }

            Sint16 value = SDL_GameControllerGetAxis(controller, sdlAxis);

            // Si checkPositive est vrai, on considère l’axe actif si value > DEADZONE
            // Si checkNegative est vrai, on considère l’axe actif si value < -DEADZONE
            if ((checkPositive && value > DEADZONE) || (checkNegative && value < -DEADZONE)) {
                currentStates[action] = true;
            }
        }
    }
}

bool InputSystem::isInputActive(int inputConfigID, const std::string& action, bool allowHold)
{
    bool prev;
    if (!allowHold) {
        prev = prevStates[action];
        prevStates[action] = currentStates[action];
    }

    async([this, inputConfigID] { updateInputs(inputConfigID); });

    if (allowHold) return currentStates[action];

    return currentStates[action] && !prev;
}
