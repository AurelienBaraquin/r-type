//
// Created by Guillaume Tran on 03/01/2025.
//

#include "Editor.hpp"
#include "raygui.h"

void Editor::run()
{
    Camera2D camera = {0};
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){_centerBox.x, _centerBox.y};
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        GuiPanel(_centerBox, "Scene");

        auto entities = getSortedEntitiesByZ();

        BeginScissorMode(_centerBox.x, _centerBox.y, _centerBox.width, _centerBox.height);
        BeginMode2D(camera);
        drawEntities(entities);
        EndMode2D();
        EndScissorMode();

        GuiPanel(_leftBox, "Lists");
        _sceneManager->drawEntities();
        GuiPanel(_rightBox, "Properties");

        EndDrawing();
    }
}

std::vector<Entity> Editor::getSortedEntitiesByZ()
{
    std::vector<Entity> entities = _engine.getRegistry().view<Components::Position>();
    std::sort(entities.begin(), entities.end(), [this](Entity a, Entity b) {
        auto positionA = _engine.getRegistry().getComponent<Components::Position>(a);
        auto positionB = _engine.getRegistry().getComponent<Components::Position>(b);
        return positionA->z < positionB->z;
    });
    return entities;
}

void Editor::drawEntities(const std::vector<Entity>& entities)
{
    for (const auto& entity : entities)
    {
        auto position = _engine.getRegistry().getComponent<Components::Position>(entity);
        auto rotation = _engine.getRegistry().getComponent<Components::Rotation>(entity);
        auto scale = _engine.getRegistry().getComponent<Components::Scale>(entity);

        float adjustedX = position->x;
        float adjustedY = _centerBox.y + position->y;
        Components::Position adjustedPosition = {(int)adjustedX, (int)adjustedY, position->z};

        if (_engine.getRegistry().hasComponent<Components::Sprite>(entity))
        {
            auto sprite = _engine.getRegistry().getComponent<Components::Sprite>(entity);
            BrutSprite bruteSpriteVar = _graphic.manageSprites().getSprite(sprite->spriteID);
            _graphic.drawTextureEx(&bruteSpriteVar, &adjustedPosition, rotation, scale);
        }
        else if (_engine.getRegistry().hasComponent<Components::Animation>(entity))
        {
            auto animation = _engine.getRegistry().getComponent<Components::Animation>(entity);
            auto frames = _graphic.manageAnimations().getAnimation(animation->animationID);
            auto currentFrame = frames[animation->currentFrame];

            BrutSprite sprite = {currentFrame.textureID, currentFrame.width, currentFrame.height,
                                 currentFrame.originX, currentFrame.originY};
            _graphic.drawTextureEx(&sprite, &adjustedPosition, rotation, scale);
        }
        else
        {
            DrawCircle(adjustedPosition.x, adjustedPosition.y, 10, RED);
        }
    }
}
