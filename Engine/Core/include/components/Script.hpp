#pragma once

#include <sol/sol.hpp>
#include <string>

namespace Components {
struct Script {
    std::string scriptPath;
    bool initialized = false;
};
}  // namespace Components
