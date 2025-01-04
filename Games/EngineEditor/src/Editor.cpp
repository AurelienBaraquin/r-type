//
// Created by Guillaume Tran on 03/01/2025.
//

#include "Editor.hpp"
#include "raygui.h"

void Editor::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        GuiPanel(_centerBox, "scene");
        std::vector<Entity> entities = _engine.getRegistry().view<Components::Position>();
        std::vector<Entity> entitiesToDraw;
        for (auto entity : entities) {
            entitiesToDraw.push_back(entity);
        }
        std::sort(entities.begin(), entities.end(), [this](Entity a, Entity b) {
            auto positionA = _engine.getRegistry().getComponent<Components::Position>(a);
            auto positionB = _engine.getRegistry().getComponent<Components::Position>(b);
            return positionA->z < positionB->z;
        });

        for (auto &entity : entities)
        {
            auto position = _engine.getRegistry().getComponent<Components::Position>(entity);
            auto rotation = _engine.getRegistry().getComponent<Components::Rotation>(entity);
            auto scale = _engine.getRegistry().getComponent<Components::Scale>(entity);
            float adjustedX = _centerBox.x + position->x;
            float adjustedY = _centerBox.y + position->y;
            Components::Position adjustedPosition = {(int)adjustedX, (int)adjustedY, position->z};

            if (!(adjustedX >= _centerBox.x && adjustedX <= _centerBox.x + _centerBox.width &&
                adjustedY >= _centerBox.y && adjustedY <= _centerBox.y + _centerBox.height))
            {
                continue;
            }

            if (_engine.getRegistry().hasComponent<Components::Sprite>(entity)) {
                std::cout << "Sprite" << std::endl;
                auto sprite = _engine.getRegistry().getComponent<Components::Sprite>(entity);
                BrutSprite bruteSpriteVar = _graphic.manageSprites().getSprite(sprite->spriteID);
                _graphic.drawTextureEx(&bruteSpriteVar, position, rotation, scale);
            } else if (_engine.getRegistry().hasComponent<Components::Animation>(entity)) {
                std::cout << "Animation" << std::endl;
                auto animation = _engine.getRegistry().getComponent<Components::Animation>(entity);
                auto frames = _graphic.manageAnimations().getAnimation(animation->animationID);
                auto currentFrame = frames[animation->currentFrame];

                auto sprite = BrutSprite{currentFrame.textureID, currentFrame.width, currentFrame.height,
                                         currentFrame.originX, currentFrame.originY};
                std::cout << position->x << " " << position->y << std::endl;
                _graphic.drawTextureEx(&sprite, &adjustedPosition, rotation, scale);
            } else {
                DrawCircle(adjustedPosition.x, adjustedPosition.y, 10, RED);
            }
        }
        std::cout << "-----------------------------" << std::endl;
        
        GuiPanel(_leftBox, "lists");
        _sceneManager->drawEntities();
        GuiPanel(_rightBox, "properties");


        EndDrawing();
    }
}