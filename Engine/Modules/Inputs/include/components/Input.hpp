#pragma once

#include <unordered_map>
#include <string>

namespace Components
{
struct Input {
    // std::unordered_map<std::string, bool> buttons;
    // std::unordered_map<std::string, float> axes;
    std::string configFile;
};
}  // namespace Components
