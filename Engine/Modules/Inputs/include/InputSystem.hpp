#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>

#include "Input.hpp"
#include "Loader.hpp"

enum class CONTROLLER_AXIS {
    LEFT_STICK_X_POSITIVE,
    LEFT_STICK_X_NEGATIVE,
    LEFT_STICK_Y_POSITIVE,
    LEFT_STICK_Y_NEGATIVE,
    RIGHT_STICK_X_POSITIVE,
    RIGHT_STICK_X_NEGATIVE,
    RIGHT_STICK_Y_POSITIVE,
    RIGHT_STICK_Y_NEGATIVE
};

static std::unordered_map<std::string, CONTROLLER_AXIS> axisMap = {
    {"LeftStickXPositive", CONTROLLER_AXIS::LEFT_STICK_X_POSITIVE},
    {"LeftStickXNegative", CONTROLLER_AXIS::LEFT_STICK_X_NEGATIVE},
    {"LeftStickYPositive", CONTROLLER_AXIS::LEFT_STICK_Y_POSITIVE},
    {"LeftStickYNegative", CONTROLLER_AXIS::LEFT_STICK_Y_NEGATIVE},
    {"RightStickXPositive", CONTROLLER_AXIS::RIGHT_STICK_X_POSITIVE},
    {"RightStickXNegative", CONTROLLER_AXIS::RIGHT_STICK_X_NEGATIVE},
    {"RightStickYPositive", CONTROLLER_AXIS::RIGHT_STICK_Y_POSITIVE},
    {"RightStickYNegative", CONTROLLER_AXIS::RIGHT_STICK_Y_NEGATIVE}};

static std::unordered_map<std::string, SDL_GameControllerButton> buttonMap = {
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

struct InputConfig {
    std::unordered_map<SDL_Scancode, std::string> buttons;
    std::unordered_map<Uint8, std::string> mouseButtons;
    std::unordered_map<SDL_GameControllerButton, std::string> controllerButtons;
    std::unordered_map<CONTROLLER_AXIS, std::string> controllerAxis;
};

class InputSystem : public ILoader
{
   public:
    // ILoader interface
    void load(const nlohmann::json& data) override;
    std::string getPart() override
    {
        return "inputConfigs";
    }

    void removeInput(int inputConfigID);
    InputConfig& getInput(int inputConfigID);

    void updateInputs(int inputConfigID);
    bool isInputActive(int inputConfigID, const std::string& action, bool allowHold = true);

    void loadKeyboardConfig(const nlohmann::json& deviceData, InputConfig& _inputConfig);
    void loadMouseConfig(const nlohmann::json& deviceData, InputConfig& _inputConfig);
    void loadControllerConfig(const nlohmann::json& deviceData, InputConfig& _inputConfig);

   private:
    std::unordered_map<int, InputConfig> configs;
    std::unordered_map<std::string, bool> currentStates;
    std::unordered_map<std::string, bool> prevStates;
    std::unordered_map<std::string, std::function<void(const nlohmann::json&, InputConfig&)>> deviceLoaders = {
        {"keyboard", [this](const nlohmann::json& data, InputConfig& config) { loadKeyboardConfig(data, config); }},
        {"mouse", [this](const nlohmann::json& data, InputConfig& config) { loadMouseConfig(data, config); }},
        {"controller", [this](const nlohmann::json& data, InputConfig& config) { loadControllerConfig(data, config); }}
    };
};
