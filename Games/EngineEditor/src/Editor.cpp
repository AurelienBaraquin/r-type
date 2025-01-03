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

        GuiPanel(leftPanel, "lists");
        GuiPanel(CenterPanel, "scene");
        GuiPanel(rightPanel, "properties");


        EndDrawing();
    }
}