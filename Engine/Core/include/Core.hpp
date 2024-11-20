#pragma once

#include <vector>

#include "EntityBuilder.hpp"
#include "Scene.hpp"
#include "SystemManager.hpp"
#include "Loader.hpp"

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

        if (std::is_base_of<ILoader, T>::value)
        {
            _loaderManager.addLoader(dynamic_cast<ILoader*>(&system));
        }

        return system;
    }

    EntityBuilder addEntity()
    {
        return EntityBuilder(_registry.createEntity(), _registry);
    }

    SceneLoader manageScene()
    {
        return SceneLoader(_componentFactory, _registry, _loaderManager);
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
    LoaderManager _loaderManager;
    ComponentFactory _componentFactory;
    Registry _registry;
};
