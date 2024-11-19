#include "Core.hpp"
#include "Registry.hpp"

void Engine::startup()
{
    for (auto& [type, system] : _systemManager)
    {
        system->startup();
    }
}

void Engine::loop()
{
    while (true)
    {
        for (auto& [type, system] : _systemManager)
        {
            system->update(0.0f, _registry);
        }
    }
}

void Engine::shutdown()
{
    for (auto& [type, system] : _systemManager)
    {
        system->shutdown();
    }
}
