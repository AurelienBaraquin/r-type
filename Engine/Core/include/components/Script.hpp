#pragma once

#include <string>
#include <sol/sol.hpp>

namespace Components {
    struct Script {
        std::string scriptPath;
        sol::state luaState;
        bool loaded = false;
    };
}
