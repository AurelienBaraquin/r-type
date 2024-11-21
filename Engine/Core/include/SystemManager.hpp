#pragma once

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

#include "ISystem.hpp"

class SystemManager
{
   public:
    template <typename T>
    T& getSystem()
    {
        auto it = _systems.find(typeid(T));
        if (it == _systems.end())
        {
            throw std::runtime_error("System not found");
        }
        return *static_cast<T*>(it->second.get());
    }

    template <typename T, typename... Args>
    void addSystem(Args&&... args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        auto ptr = system.get();
        _systems[typeid(T)] = std::move(system);
    }

    template <typename T>
    void removeSystem()
    {
        auto it = _systems.find(typeid(T));
        if (it != _systems.end())
        {
            _systems.erase(it);
        }
    }

    void clear()
    {
        _systems.clear();
    }

    template <typename T>
    bool hasSystem() const
    {
        return _systems.find(typeid(T)) != _systems.end();
    }

    auto begin() noexcept
    {
        return _systems.begin();
    }

    auto end() noexcept
    {
        return _systems.end();
    }

    auto begin() const noexcept
    {
        return _systems.begin();
    }

    auto end() const noexcept
    {
        return _systems.end();
    }

   private:
    std::unordered_map<std::type_index, std::unique_ptr<ISystem>> _systems;
};
