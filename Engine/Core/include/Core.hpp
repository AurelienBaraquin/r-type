#pragma once

#include <vector>

#include "EntityBuilder.hpp"
#include "Scene.hpp"
#include "SystemManager.hpp"

class Engine : public ISystem
{
   public:
    Engine()
    {
        registerComponentFactory(_componentFactory);
    }

    Engine& operator=(const Engine&) = delete;

    template <typename T, typename... Args>
    T& addModule(Args&&... args)
    {
        _systemManager.addSystem<T>(std::forward<Args>(args)...);
        auto& system = _systemManager.getSystem<T>();
        system.registerComponentFactory(_componentFactory);
        return system;
    }

    EntityBuilder addEntity()
    {
        return EntityBuilder(_registry.createEntity(), _registry);
    }

    SceneLoader manageScene()
    {
        return SceneLoader(_componentFactory, _registry);
    }

    void run()
    {
        startup();
        loop();
        shutdown();
    }

   private:
    void startup();
    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;
    void loop();
    void shutdown();

    void updateScript();
    void update(float deltaTime, Registry& registry) override
    {
    }

    ScriptSystem _ScriptSystem;
    SystemManager _systemManager;
    ComponentFactory _componentFactory;
    Registry _registry;
};
