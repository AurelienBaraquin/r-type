#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>

#include "Input.hpp"

enum class CONTROLLER_AXIS
{
    LEFT_STICK_X_POSITIVE,
    LEFT_STICK_X_NEGATIVE,
    LEFT_STICK_Y_POSITIVE,
    LEFT_STICK_Y_NEGATIVE,
    RIGHT_STICK_X_POSITIVE,
    RIGHT_STICK_X_NEGATIVE,
    RIGHT_STICK_Y_POSITIVE,
    RIGHT_STICK_Y_NEGATIVE
};

struct InputConfig
{
    std::unordered_map<SDL_Scancode, std::string> buttons;
    std::unordered_map<Uint8, std::string> mouseButtons;
    std::unordered_map<SDL_GameControllerButton, std::string> controllerButtons;
    std::unordered_map<CONTROLLER_AXIS, std::string> controllerAxis;
};

class InputSystem
{
   public:
    void loadInput(const std::string& configFile);
    void removeInput(const std::string& configFile);
    InputConfig& getInput(const std::string& configFile);

   private:
    std::unordered_map<std::string, InputConfig> inputs;
};
