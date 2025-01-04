//
// Created by Guillaume Tran on 03/01/2025.
//

#include "SceneManager.hpp"
#include "raygui.h"


void SceneManager::drawEntities()
{
    int i = 0;
    for (auto &entity : _entities)
    {
        std::string entityName = "Entity " + std::to_string(static_cast<int>(entity));
        if (GuiButton(Rectangle{0, (float)i * 20, 200, 20}, entityName.c_str()))
        {
            _selectedEntity = entity;
        }
        i++;
    }   
}