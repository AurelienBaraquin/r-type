#include "Core.hpp"

#include "Registry.hpp"

void Engine::startup()
{
    for (auto& [type, system] : _systemManager)
    {
        system->registerScriptBindings(_ScriptSystem, _registry);
    }
    registerScriptBindings(_ScriptSystem, _registry);
}

#include <chrono>
#include <thread>

void Engine::loop()
{
    bool running = true;

    eventManager->subscribe<Events::Shutdown>([&running](std::shared_ptr<Event> event)
                                              { running = false; });

    while (running)
    {
        updateScript();
        for (auto& [type, system] : _systemManager)
        {
            system->update(1.0f, _registry, _ScriptSystem);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
}

void Engine::shutdown()
{
    _systemManager.clear();
}

void Engine::updateScript()
{
    for (auto entity : _registry.view<Components::Script>())
    {
        auto* script = _registry.getComponent<Components::Script>(entity);

        sol::state& luaState = _ScriptSystem.getScript(script->scriptPath);

        //        if (luaState["onCollide"](entity))
        //        {
        //            auto* area2D = _registry.getComponent<Components::Area2D>(entity);
        //            if (area2D) {
        //                if (area2D->firstCollidedEntity) {
        //                    luaState["onCollide"](area2D->firstCollidedEntity);
        //                    area2D->firstCollidedEntity = 0;
        //                }
        //            }
        //        }

        if (luaState["update"])
        {
            luaState["update"](entity);
        }
    }
}
