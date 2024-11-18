#pragma once

#include "ModuleManager.hpp"
#include <vector>
#include "Registry.hpp"

class Core {
public:
    Core();
    ~Core();

    void run();

    static void assert(bool condition, const char* message) {
        if (!condition)
            throw std::runtime_error(message);
    }
private:
    ModuleManager _moduleManager;
    Registry _registry;
};
