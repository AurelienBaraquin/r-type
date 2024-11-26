#include "Core.hpp"

#include "Registry.hpp"

void Engine::startup()
{
    for (auto& [type, system] : _systemManager) {
        system->registerScriptBindings(_ScriptSystem, _registry);
    }
    registerScriptBindings(_ScriptSystem, _registry);
}

#include <chrono>
#include <thread>

void Engine::loop()
{
    bool running = true;

    eventManager->subscribe<Events::Shutdown>(
        [&running](std::shared_ptr<Event> event) { running = false; });
//    _lastTime = std::chrono::high_resolution_clock::now();
    while (running) {
//        auto currentTime = std::chrono::high_resolution_clock::now();
//        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - _lastTime).count();
//        _lastTime = currentTime;
        float deltaTime = 1.0f / 60.0f; // TEMPORARY
        //TO DO changer le deltatime
        updateScript(deltaTime);
        for (auto& [type, system] : _systemManager) {
            system->update(1.0f, _registry, _ScriptSystem);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
}

void Engine::shutdown()
{
    _systemManager.clear();
}

void Engine::updateScript(float deltaTime)
{
    for (auto entity : _registry.view<Components::Script>()) {
        auto* script = _registry.getComponent<Components::Script>(entity);

        sol::state& luaState = _ScriptSystem.getScript(entity, script->scriptPath);
        if (!script->initialized) {
            if (luaState["init"]) {
                luaState["init"](entity);
            }
            script->initialized = true;
        }
        if (luaState["update"]) {
            luaState["update"](deltaTime);
        }
    }
}
