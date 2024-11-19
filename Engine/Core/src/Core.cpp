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
        std::this_thread::sleep_for(std::chrono::milliseconds(160));
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

        if (script->loaded == false) {
            script->luaState = sol::state();

            script->luaState.open_libraries(sol::lib::base, sol::lib::math);
            _scriptManager.applyBindings(script->luaState, entity);
            script->luaState.script_file(script->scriptPath);

            script->loaded = true;
        }

        if (script->luaState["update"]) {
            script->luaState["update"]();
        }
    }
}
