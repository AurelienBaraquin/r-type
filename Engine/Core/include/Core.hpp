#pragma once

#include <vector>

#include "EntityBuilder.hpp"
#include "Loader.hpp"
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
        if (_systemManager.hasSystem<T>()) {
            Logger::getInstance().error("System already registered");
            return _systemManager.getSystem<T>();
        }
        _systemManager.addSystem<T>(std::forward<Args>(args)...);
        auto& system = _systemManager.getSystem<T>();
        system.registerComponentFactory(_componentFactory);

        if (std::is_base_of<ILoader, T>::value) {
            _loaderManager.addLoader(dynamic_cast<ILoader*>(&system));
        }

        return system;
    }

    EntityBuilder addEntity() // useless ?
    {
        return EntityBuilder(_registry.createEntity(), _registry);
    }

    void loadScene(const std::string& filePath)
    {
        SceneLoader(_componentFactory, _registry, _loaderManager).loadScene(filePath);
    }

    void run()
    {
        startup();
        loop();
        shutdown();
    }

    ScriptSystem& getScriptSystem()
    {
        return _ScriptSystem;
    }

   private:
    void startup();
    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;
    void loop();
    void shutdown();

    void updateScript(float deltaTime);
    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override
    {
    }

    ScriptSystem _ScriptSystem;
    SystemManager _systemManager;
    LoaderManager _loaderManager;
    ComponentFactory _componentFactory;
    Registry _registry;
    std::chrono::_V2::system_clock::time_point _lastTime;
};
