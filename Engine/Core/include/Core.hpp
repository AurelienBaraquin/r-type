#pragma once

#include <vector>

#include "EntityBuilder.hpp"
#include "Scene.hpp"
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

    SceneLoader ManageScene()
    {
        return SceneLoader(_componentFactory, _registry);
    }

    void initModules()
    {
        for (auto& [type, system] : _systemManager)
        {
            system->registerComponentFactory(_componentFactory);
        }
        registerComponentFactory(_componentFactory);
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
    void registerComponentFactory(ComponentFactory& componentFactory) override;
    void loop();
    void shutdown();

    void updateScript();
    void update(float deltaTime, Registry& registry) override
    {
    }

    ScriptManager _scriptManager;
    SystemManager _systemManager;
    ComponentFactory _componentFactory;
    Registry _registry;
};
