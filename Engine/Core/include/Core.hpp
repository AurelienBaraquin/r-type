#pragma once

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

#include "EntityBuilder.hpp"
#include "Loader.hpp"
#include "Scene.hpp"
#include "SystemManager.hpp"


#include "Json.hpp"

// TODO
// j'ai mis en notThreadable pour le moment car crash lors de
//if (luaState["update"]) { <--- crash voir notion
//    luaState["update"](deltaTime);
//}
// dans updateScript
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

        if (std::is_base_of<NotThreadable, T>::value) {
            _notThreadableModules.push_back(&system);
        }

        return system;
    }

    EntityBuilder addEntity()
    {
        return EntityBuilder(_registry.createEntity(), _registry);
    }

    void loadScene(const std::string& filePath, bool reload=false)
    {
        SceneLoader(_componentFactory, _registry, _loaderManager, _entityTemplateManager)
            .loadScene(filePath, reload);
    }


    void changeScene(const std::string& filePath)
    {
        SceneLoader(_componentFactory, _registry, _loaderManager, _entityTemplateManager)
            .changeScene(filePath);
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

    Registry& getRegistry()
    {
        return _registry;
    }

    SystemManager& getSystemManager()
    {
        return _systemManager;
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
    std::vector<ISystem*> _notThreadableModules;
    LoaderManager _loaderManager;
    ComponentFactory _componentFactory;
    Registry _registry;
    EntityTemplateManager _entityTemplateManager;

    std::vector<std::thread> _threads;
};
