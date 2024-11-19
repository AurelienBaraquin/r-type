#include "Core.hpp"
#include "Registry.hpp"

void Engine::startup()
{
    for (auto& [type, system] : _systemManager)
    {
        system->startup();
        system->registerScriptBindings(_scriptManager, _registry);
    }
    registerScriptBindings(_scriptManager, _registry);
}

#include <thread>
#include <chrono>

void Engine::loop()
{
    while (true)
    {
        updateScript();
        for (auto& [type, system] : _systemManager)
        {
            system->update(0.0f, _registry);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Engine::shutdown()
{
    for (auto& [type, system] : _systemManager)
    {
        system->shutdown();
    }
}

void Engine::updateScript() {
    for (auto entity : _registry.view<Components::Script>()) {
        auto* script = _registry.getComponent<Components::Script>(entity);

        sol::state& luaState = _scriptManager.getScript(script->scriptPath, entity);

        if (luaState["update"]) {
            luaState["update"]();
        }
    }
}
