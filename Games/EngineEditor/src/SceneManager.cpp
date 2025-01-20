//
// Created by Guillaume Tran on 03/01/2025.
//

#include "SceneManager.hpp"

#include "raygui.h"

void SceneManager::drawEntities(int padding)
{
    int i = 0;
    for (auto &entity : _entities) {
        std::vector tags = _registry.getTags(entity);
        if (tags.empty()) {
            tags.push_back("No tag");
        }
        std::string entityName = "Entity " + std::to_string(entity) + " - " + tags[0];
        if (GuiButton(Rectangle{0, (float)i * 20 + padding, 200, 20}, entityName.c_str())) {
            _selectedEntity = entity;
            std::cout << "Selected entity: " << _selectedEntity << std::endl;
        }
        i++;
    }
}