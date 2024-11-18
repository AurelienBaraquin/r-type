#pragma once

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

#include "IModule.hpp"

class ModuleManager
{
   public:
    template <typename T>
    T& getModule()
    {
        auto it = _modules.find(typeid(T));
        if (it == _modules.end())
        {
            throw std::runtime_error("Module not found");
        }
        return *static_cast<T*>(it->second.get());
    }

    template <typename T, typename... Args>
    T& addModule(Args&&... args)
    {
        auto module = std::make_unique<T>(std::forward<Args>(args)...);
        auto ptr = module.get();
        _modules[typeid(T)] = std::move(module);
        return *ptr;
    }

    template <typename T>
    void removeModule()
    {
        auto it = _modules.find(typeid(T));
        if (it != _modules.end())
        {
            _modules.erase(it);
        }
    }

   private:
    std::unordered_map<std::type_index, std::unique_ptr<IModule>> _modules;
};
