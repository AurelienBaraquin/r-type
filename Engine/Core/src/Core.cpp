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
    // std::cout << "Core: Update script\n";
    for (auto entity : _registry.view<Components::Script>()) {
        // std::cout << "Core: Update script: Get script of " << entity << "\n";
        // std::cout << "get " << _registry.getComponent<Components::Json>(entity) << "\n";
        if (!_registry.getComponent<Components::Script>(entity)) {
            continue;
        }
        auto* script = _registry.getComponent<Components::Script>(entity);
        // std::cout << "Core: Update script: " << script->scriptPath << "\n";
        sol::state& luaState = _ScriptSystem.getScript(entity, script->scriptPath);
        // std::cout << "Core: Update script: Got lua state\n";
        if (!script->initialized) {
            // std::cout << "Core: Update script: Initialize script\n";
            if (luaState["init"]) {
                luaState["init"](entity);
            }
            script->initialized = true;
        }
        if (luaState["update"]) {
            // std::cout << "Core: Update script: Call update\n";
            luaState["update"](deltaTime);
            // std::cout << "Core: Update script: End call update\n";
        }
    }
    // std::cout << "Core: End update script\n";
}
