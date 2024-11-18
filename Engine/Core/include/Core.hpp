#pragma once

#include "ModuleManager.hpp"
#include <vector>
#include "Registry.hpp"

class Core {
public:
    Core();
    ~Core();

    void run();
private:
    ModuleManager _moduleManager;
    Registry _registry;
};
