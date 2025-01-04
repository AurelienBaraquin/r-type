//
// Created by Guillaume Tran on 03/01/2025.
//

#pragma once

#define BUILD_GRAPHIC
#define BUILD_PHYSICS
#define BUILD_AUDIO
#define BUILD_INPUTS
#include "Engine.hpp"
#include "SceneManager.hpp"
#include <memory>
#include "raylib.h"
#include "Scene.hpp"

class Editor
{
public:
    Editor() : _graphic(_engine.addModule<Graphic>("R-Type", 1, 1))
    {
        // engine.addModule<Inputs>();
        _engine.addModule<Physics>();
        InitWindow(1920, 1080, "Engine Editor");
        _engine.loadScene("Games/RType/config/scene.json");
        _sceneManager = std::make_shared<SceneManager>(_engine.getRegistry().view<>());

        float _width = (float)GetScreenWidth();
        float _height = (float)GetScreenHeight();
        _leftBox = {0, 0, _width * 0.20f, _height};
        _centerBox = {_leftBox.width, 0,_width * 0.60f, _height};
        _rightBox = {_centerBox.x + _centerBox.width, 0, _width * 0.20f, _height};
    }

    ~Editor()
    {
    }

    void run();

    void setEntities(std::vector<Entity> entities)
    {
        _entities = entities;
    }

private:
    Engine _engine;
    std::vector<Entity> _entities;
    std::shared_ptr<SceneManager> _sceneManager;
    Graphic& _graphic;
    float _width = 0;
    float _height = 0;
    Rectangle _leftBox;
    Rectangle _centerBox;
    Rectangle _rightBox;
};
