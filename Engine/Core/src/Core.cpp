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
    bool running = true;

    eventManager->subscribe<Events::Shutdown>([&running](std::shared_ptr<Event> event) {
        running = false;
    });

    while (running)
    {
        updateScript();
        for (auto& [type, system] : _systemManager)
        {
            system->update(1.0f, _registry);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
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

        sol::state& luaState = _scriptManager.getScript(script->scriptPath);

        if (luaState["update"]) {
            luaState["update"](entity);
        }
    }
}
