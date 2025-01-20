//
// Created by Guillaume Tran on 03/01/2025.
//

#include "Editor.hpp"

#include <nlohmann/json.hpp>

#include "raygui.h"

void Editor::run()
{
    _camera = {0};
    _camera.target = (Vector2){0, 0};
    _camera.offset = (Vector2){_centerBox.x, _centerBox.y};
    _camera.zoom = 1.0f;

    std::vector<Entity> unfilteredEntities = _engine.getRegistry().view<Components::Json>();
    for (const auto& entity : unfilteredEntities) {
        std::vector<std::string> tags = _engine.getRegistry().getTags(entity);
    }
    Entity oldSelectedEntity = -1;

    while (!WindowShouldClose()) {
        drawEditor(_camera, oldSelectedEntity);
        if (handleInputs()) {
            break;
        }    
    }

    CloseWindow();

    if (_launchScene) {
        runGame();
    }

    return;
}

void Editor::runGame()
{
    Engine engine;
    engine.addModule<Graphic>("game", 384 * 2, 256 * 2);
    engine.addModule<Inputs>();
    engine.addModule<Physics>();
    engine.addModule<Audio>();

    engine.loadScene(_scenePath);
    engine.run();
}

void Editor::drawEditor(Camera2D camera, Entity& oldSelectedEntity)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    GuiPanel(_centerBox, "Scene");
    // GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x000000FF);
    auto entities = getSortedEntitiesByZ();
    BeginScissorMode(_centerBox.x, _centerBox.y, _centerBox.width, _centerBox.height);
    BeginMode2D(camera);
    drawEntities(entities);
    EndMode2D();
    EndScissorMode();

    GuiPanel(_leftBox, "Lists");
    char* label = _scenePath.data();
    if (GuiTextBox(Rectangle{_leftBox.x + 10, _leftBox.y + 25, 200, 20}, label, 100,
                    editScene)) {
        editScene = !editScene;
        _scenePath = label;
    }

    _sceneManager->drawEntities(50);
    GuiPanel(_rightBox, "Properties");
    int padding = 25;
    drawProperties(padding, TextBoxesBool, oldSelectedEntity);

    EndDrawing();
}

bool Editor::handleInputs()
{
    if (IsKeyPressed(KEY_F1)) {
        saveScene();
    }
    if (IsKeyPressed(KEY_F2)) {
        reloadScene();
    }
    if (IsKeyPressed(KEY_F5)) {
        _launchScene = true;
        return true;
    }
    for (KeyboardKey pressedKey : _pressedKeys) {
        if (pressedKey == (KEY_UP)) _camera.offset.y += 10;
        if (pressedKey == (KEY_DOWN)) _camera.offset.y -= 10;
        if (pressedKey == (KEY_LEFT)) _camera.offset.x += 10;
        if (pressedKey == (KEY_RIGHT)) _camera.offset.x -= 10;
    }
    std::vector<KeyboardKey> keyToCheck = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
    for (KeyboardKey key : keyToCheck) {
        if (IsKeyPressed(key)) {
            _pressedKeys.push_back(key);
        }
        if (IsKeyReleased(key)) {
            _pressedKeys.erase(std::remove(_pressedKeys.begin(), _pressedKeys.end(), key),
                               _pressedKeys.end());
        }
    }
    return false;
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
    for (const auto& entity : entities) {
        auto position = _engine.getRegistry().getComponent<Components::Position>(entity);
        auto rotation = _engine.getRegistry().getComponent<Components::Rotation>(entity);
        auto scale = _engine.getRegistry().getComponent<Components::Scale>(entity);

        float adjustedX = position->x;
        float adjustedY = _centerBox.y + position->y;
        Components::Position adjustedPosition = {(int)adjustedX, (int)adjustedY, position->z};

        if (_engine.getRegistry().hasComponent<Components::Sprite>(entity)) {
            auto sprite = _engine.getRegistry().getComponent<Components::Sprite>(entity);
            BrutSprite bruteSpriteVar = _graphic.manageSprites().getSprite(sprite->spriteID);
            _graphic.drawTextureEx(&bruteSpriteVar, &adjustedPosition, rotation, scale);
        } else if (_engine.getRegistry().hasComponent<Components::Animation>(entity)) {
            auto animation = _engine.getRegistry().getComponent<Components::Animation>(entity);
            auto frames = _graphic.manageAnimations().getAnimation(animation->animationID);
            auto currentFrame = frames[animation->currentFrame];

            BrutSprite sprite = {currentFrame.textureID, currentFrame.width, currentFrame.height,
                                 currentFrame.originX, currentFrame.originY};
            _graphic.drawTextureEx(&sprite, &adjustedPosition, rotation, scale);
        } else {
            DrawCircle(adjustedPosition.x, adjustedPosition.y, 10, RED);
        }
    }
}

void Editor::drawProperties(int& padding, std::vector<bool>& TextBoxesBool,
                            Entity& oldSelectedEntity)
{
    if (_selectedEntity == -1) {
        return;
    }

    auto jsonComponent = _engine.getRegistry().getComponent<Components::Json>(_selectedEntity);
    std::string jsonString = jsonComponent->data;
    nlohmann::json json = nlohmann::json::parse(jsonString);
    int iComponent = 0;

    for (auto it = json["components"].begin(); it != json["components"].end(); ++it) {
        GuiLabel(Rectangle{_rightBox.x + 10, _rightBox.y + padding, 100, 20}, it.key().c_str());
        for (auto it2 = it.value().begin(); it2 != it.value().end(); ++it2) {
            if (_selectedEntity != oldSelectedEntity) {
                TextBoxesBool.push_back(false);
                oldSelectedEntity = _selectedEntity;
            }

            std::string value;
            if (it2->is_string()) {
                value = it2->get<std::string>();
            } else if (it2->is_number()) {
                value = std::to_string(it2->get<float>());
            } else if (it2->is_boolean()) {
                value = it2->get<bool>() ? "true" : "false";
            }

            std::string valueMemory = value;
            char* label = value.data();
            padding += 20;

            if (GuiTextBox(Rectangle{_rightBox.x + 110, _rightBox.y + padding, 100, 20}, label, 100,
                           TextBoxesBool[iComponent])) {
                TextBoxesBool[iComponent] = !TextBoxesBool[iComponent];
                if (!TextBoxesBool[iComponent]) {
                    saveScene();
                    reloadScene();
                    return;
                }
            }

            if (valueMemory != value) {
                bool changed = true;
                if (it2->is_number()) {
                    *it2 = std::stof(value);
                } else if (it2->is_boolean()) {
                    *it2 = value == "true";
                } else if (it2->is_string()) {
                    *it2 = value;
                } else {
                    changed = false;
                    std::cout << "Type not supported" << std::endl;
                }
                if (changed) {
                    std::string newJsonString = json.dump();
                    jsonComponent->data = newJsonString;
                }
            }

            iComponent++;
        }
        padding += 40;
    }
}

Camera2D Editor::setCamera()
{
    Camera2D camera = {0};
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){_centerBox.x, _centerBox.y};
    camera.zoom = 1.0f;
    return camera;
}