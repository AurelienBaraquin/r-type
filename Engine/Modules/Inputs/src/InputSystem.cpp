#include "InputSystem.hpp"

#include <SDL2/SDL.h>

#include <fstream>
#include <nlohmann/json.hpp>

std::unordered_map<std::string, CONTROLLER_AXIS> axisMap = {
    {"LeftStickXPositive", CONTROLLER_AXIS::LEFT_STICK_X_POSITIVE},
    {"LeftStickXNegative", CONTROLLER_AXIS::LEFT_STICK_X_NEGATIVE},
    {"LeftStickYPositive", CONTROLLER_AXIS::LEFT_STICK_Y_POSITIVE},
    {"LeftStickYNegative", CONTROLLER_AXIS::LEFT_STICK_Y_NEGATIVE},
    {"RightStickXPositive", CONTROLLER_AXIS::RIGHT_STICK_X_POSITIVE},
    {"RightStickXNegative", CONTROLLER_AXIS::RIGHT_STICK_X_NEGATIVE},
    {"RightStickYPositive", CONTROLLER_AXIS::RIGHT_STICK_Y_POSITIVE},
    {"RightStickYNegative", CONTROLLER_AXIS::RIGHT_STICK_Y_NEGATIVE}};

std::unordered_map<std::string, SDL_GameControllerButton> buttonMap = {
    {"A", SDL_CONTROLLER_BUTTON_A},
    {"B", SDL_CONTROLLER_BUTTON_B},
    {"X", SDL_CONTROLLER_BUTTON_X},
    {"Y", SDL_CONTROLLER_BUTTON_Y},
    {"Back", SDL_CONTROLLER_BUTTON_BACK},
    {"Guide", SDL_CONTROLLER_BUTTON_GUIDE},
    {"Start", SDL_CONTROLLER_BUTTON_START},
    {"LeftStick", SDL_CONTROLLER_BUTTON_LEFTSTICK},
    {"RightStick", SDL_CONTROLLER_BUTTON_RIGHTSTICK},
    {"LeftShoulder", SDL_CONTROLLER_BUTTON_LEFTSHOULDER},
    {"RightShoulder", SDL_CONTROLLER_BUTTON_RIGHTSHOULDER},
    {"DPadUp", SDL_CONTROLLER_BUTTON_DPAD_UP},
    {"DPadDown", SDL_CONTROLLER_BUTTON_DPAD_DOWN},
    {"DPadLeft", SDL_CONTROLLER_BUTTON_DPAD_LEFT},
    {"DPadRight", SDL_CONTROLLER_BUTTON_DPAD_RIGHT}};

void InputSystem::loadInput(int inputConfigID, const std::string& configFile)
{
    if (inputs.find(inputConfigID) != inputs.end())
        throw std::runtime_error("Input config already loaded: " + std::to_string(inputConfigID));

    std::ifstream file(configFile);
    nlohmann::json data;
    file >> data;

    InputConfig inputConfig;

    for (const auto& [device, deviceData] : data.items())
    {
        for (const auto& [str, code] : deviceData.items())
        {
            if (device == "keyboard")
            {
                SDL_Scancode scancode = SDL_GetScancodeFromName(code.get<std::string>().c_str());
                if (scancode == SDL_SCANCODE_UNKNOWN)
                    throw std::runtime_error("Unknown scancode: " + code.get<std::string>());
                inputConfig.buttons[scancode] = str;
            }
            else if (device == "mouse")
            {
                std::string button = code.get<std::string>();
                if (button == "LeftButton")
                    inputConfig.mouseButtons[SDL_BUTTON_LEFT] = str;
                else if (button == "MiddleButton")
                    inputConfig.mouseButtons[SDL_BUTTON_MIDDLE] = str;
                else if (button == "RightButton")
                    inputConfig.mouseButtons[SDL_BUTTON_RIGHT] = str;
                else
                    throw std::runtime_error("Unknown mouse button: " + button);
            }
            else if (device == "controller")
            {
                if (code.get<std::string>().find("Stick") != std::string::npos)
                {
                    if (axisMap.find(code.get<std::string>()) == axisMap.end())
                        throw std::runtime_error("Unknown controller axis: " +
                                                 code.get<std::string>());
                    inputConfig.controllerAxis[axisMap[code.get<std::string>()]] = str;
                }
                else
                {
                    if (buttonMap.find(code.get<std::string>()) == buttonMap.end())
                        throw std::runtime_error("Unknown controller button: " +
                                                 code.get<std::string>());
                    inputConfig.controllerButtons[buttonMap[code.get<std::string>()]] = str;
                }
            }
            else
            {
                throw std::runtime_error("Unknown device: " + device);
            }
        }
    }

    inputs[inputConfigID] = inputConfig;
}

void InputSystem::removeInput(int inputConfigID)
{
    inputs.erase(inputConfigID);
}

InputConfig& InputSystem::getInput(int inputConfigID)
{
    return inputs[inputConfigID];
}
