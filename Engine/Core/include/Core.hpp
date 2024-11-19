#pragma once

#include <vector>

#include "SystemManager.hpp"
#include "EntityBuilder.hpp"

class Engine {
public:
    Engine() = default;

    Engine& operator=(const Engine&) = delete;

    template <typename T, typename... Args>
    T& addModule(Args&&... args) {
        _systemManager.addSystem<T>(std::forward<Args>(args)...);
        return _systemManager.getSystem<T>();
    }

    EntityBuilder addEntity() {
        return EntityBuilder(_registry.createEntity(), _registry);
    }

    void run() {
        startup();
        loop();
        shutdown();
    }

private:
    void startup();
    void loop();
    void shutdown();

    SystemManager _systemManager;
    Registry _registry;
};
