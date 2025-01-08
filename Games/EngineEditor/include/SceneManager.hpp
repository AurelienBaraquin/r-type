//
// Created by Guillaume Tran on 03/01/2025.
//

#ifndef B_CPP_500_MPL_5_2_RTYPE_GUILLAUME1_TRAN_SCENEMANAGER_HPP
#define B_CPP_500_MPL_5_2_RTYPE_GUILLAUME1_TRAN_SCENEMANAGER_HPP
#include "raylib.h"
#include "Engine.hpp"

class SceneManager
{
public:
    SceneManager(Registry& registry, Entity &selectedEntity) : _registry(registry), _selectedEntity(selectedEntity) {
        _entities = _registry.view<>();
    }
    ~SceneManager() = default;

    void drawEntities();
   private:
    std::vector<Entity> _entities;
    Entity& _selectedEntity;
    Registry &_registry;
};

#endif  // B_CPP_500_MPL_5_2_RTYPE_GUILLAUME1_TRAN_SCENEMANAGER_HPP
