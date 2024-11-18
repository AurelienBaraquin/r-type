#pragma once

#include <vector>

#include "ModuleManager.hpp"
#include "Registry.hpp"

class Core
{
   public:
    Core();
    ~Core();

    void run();

   private:
    ModuleManager _moduleManager;
    Registry _registry;
};
