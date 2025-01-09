//
// Created by Guillaume Tran on 03/01/2025.
//

#pragma once

#include <memory>
#include "raylib.h"
#include "Scene.hpp"

class Editor
{
public:
    Editor()
    {
        InitWindow(800, 450, "Engine Editor");
    }

    ~Editor()
    {
    }
    void run();

private:
    std::shared_ptr<Scene> scene;


    Rectangle leftPanel = {0, 0, 200, 450};
    Rectangle CenterPanel = {200, 0, 600, 450};
    Rectangle rightPanel = {600, 0, 200, 450};
};
