//
// Created by Guillaume Tran on 03/01/2025.
//

#pragma once

#define BUILD_GRAPHIC
#define BUILD_PHYSICS
#define BUILD_AUDIO
#define BUILD_INPUTS
#include <algorithm>
#include <memory>

#include "Engine.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "raylib.h"

class Editor
{
   public:
    Editor() : _graphic(_engine.addModule<Graphic>("R-Type", 1, 1))
    {
        _scenePath = "Games/RType/config/scene.json";
        _engine.addModule<Physics>();
        _engine.addModule<Inputs>();
        InitWindow(1920, 1080, "Engine Editor");
        std::ifstream file(_scenePath);
        file >> _sceneData;
        file.close();
        _engine.loadScene(_scenePath);
        _sceneManager = std::make_shared<SceneManager>(_engine.getRegistry(), _selectedEntity);

        float _width = (float)GetScreenWidth();
        float _height = (float)GetScreenHeight();
        _leftBox = {0, 0, _width * 0.20f, _height};
        _centerBox = {_leftBox.width, 0, _width * 0.60f, _height};
        _rightBox = {_centerBox.x + _centerBox.width, 0, _width * 0.20f, _height};
        _selectedEntity = -1;
    }

    ~Editor()
    {
    }

    void run();
    void drawScene();
    void reloadScene()
    {
        std::cout << _scenePath << std::endl;
        _engine.reloadScene(_scenePath);
    }
    void drawEntities(const std::vector<Entity>& entities);
    std::vector<Entity> getSortedEntitiesByZ();

    void setEntities(std::vector<Entity> entities)
    {
        _entities = entities;
    }

    void saveScene()
    {
        std::vector<Entity> entities = _engine.getRegistry().view<>();
        std::reverse(entities.begin(), entities.end());
        nlohmann::json sceneData;

        for (auto& entity : entities) {
            auto json = _engine.getRegistry().getComponent<Components::Json>(entity);
            sceneData["entities"].push_back(json->data);
        }

        for (auto it = _sceneData.begin(); it != _sceneData.end(); ++it) {
            if (it.key() != "entities") {
                sceneData[it.key()] = it.value();
            }
        }
        std::ofstream file(_scenePath);
        file << sceneData.dump(4);
        file.close();
    }

    void drawProperties(int& padding, std::vector<bool>& TextBoxesBool, Entity& oldSelectedEntity);
private:
    nlohmann::json _sceneData;
    
    Engine _engine;
    std::vector<Entity> _entities;
    Entity _selectedEntity;
    std::shared_ptr<SceneManager> _sceneManager;

    Graphic& _graphic;
    float _width = 0;
    float _height = 0;
    Rectangle _leftBox;
    Rectangle _centerBox;
    Rectangle _rightBox;
    
    std::string _scenePath;
    bool editScene = false;
    bool _launchScene = false;
};
