#include "Inputs.hpp"

void Inputs::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    #ifdef CLIENT
        SDL_PumpEvents();
    #elif SERVER
        // Get from network
    #else
        #error "Neither CLIENT nor SERVER is defined"
    #endif
}