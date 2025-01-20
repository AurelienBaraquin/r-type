#include "Core.hpp"

#include "Registry.hpp"

void Engine::startup()
{
    for (auto& [type, system] : _systemManager) {
        system->registerScriptBindings(_ScriptSystem, _registry);
    }
    registerScriptBindings(_ScriptSystem, _registry);
}

void Engine::loop()
{
    std::atomic<bool> running = true;
    std::atomic<float> deltaTime = 1.0f / 60.0f;

    eventManager->subscribe<Events::Shutdown>(
        [&running](std::shared_ptr<Event> event) { running = false; });

    for (auto& [type, system] : _systemManager) {
        if (dynamic_cast<NotThreadable*>(system.get())) {
            continue;
        }

        _threads.push_back(std::thread([&system, &running, &deltaTime, this]() {
            while (running) {
                system->update(deltaTime, _registry, _ScriptSystem);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
            }
        }));
    }

    while (running) {
        for (auto* system : _notThreadableModules) {
            system->update(deltaTime, _registry, _ScriptSystem);
        }
        async([this, &deltaTime]() { updateScript(deltaTime); });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    for (auto& thread : _threads) {
        thread.join();
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
            continue;
        }
        if (luaState["update"]) {
            luaState["update"](deltaTime);
        }
    }
}
