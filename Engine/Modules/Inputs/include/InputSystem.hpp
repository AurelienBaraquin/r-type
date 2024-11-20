#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>
#include <string>

#include "Loader.hpp"
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

class InputSystem : public ILoader
{
   public:
    void load(const std::string& configFile) override;
    void removeInput(int inputConfigID);
    InputConfig& getInput(int inputConfigID);

   private:
    std::unordered_map<int, InputConfig> inputs;
};
