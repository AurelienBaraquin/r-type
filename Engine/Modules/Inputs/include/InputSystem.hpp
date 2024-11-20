#pragma once

#include "Input.hpp"
#include <unordered_map>

struct InputConfig
{
    std::unordered_map<std::string, bool> buttons;
    std::unordered_map<std::string, float> axes;
};

class InputSystem {
    public:
     void loadInput(const std::string& configFile);
     void removeInput(const std::string& configFile);
     Components::Input getInput(const std::string& configFile);
    
    private:
     std::unordered_map<std::string, InputConfig> inputs;
};
