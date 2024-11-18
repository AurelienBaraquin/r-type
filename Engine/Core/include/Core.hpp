#pragma once

#include <vector>

#include "SystemManager.hpp"
#include "Registry.hpp"

class Engine {
public:
    Engine() = default;

    Engine& operator=(const Engine&) = delete;

    template <typename T, typename... Args>
    Engine& addSystem(Args&&... args) {
        _systemManager.addSystem<T>(std::forward<Args>(args)...);
        return *this;
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
