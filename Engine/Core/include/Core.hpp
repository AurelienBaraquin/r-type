#pragma once

#include <vector>

#include "EntityBuilder.hpp"
#include "SystemManager.hpp"

class Engine : public ISystem
{
   public:
    Engine() = default;

    Engine& operator=(const Engine&) = delete;

    template <typename T, typename... Args>
    T& addModule(Args&&... args)
    {
        _systemManager.addSystem<T>(std::forward<Args>(args)...);
        return _systemManager.getSystem<T>();
    }

    EntityBuilder addEntity()
    {
        return EntityBuilder(_registry.createEntity(), _registry);
    }

    void run()
    {
        startup();
        loop();
        shutdown();
    }

   private:
    void startup();
    void registerScriptBindings(ScriptManager& scriptManager, Registry& registry) override;
    void loop();
    void shutdown();

    void updateScript();
    void update(float deltaTime, Registry& registry) override
    {
    }

    ScriptManager _scriptManager;
    SystemManager _systemManager;
    Registry _registry;
};
