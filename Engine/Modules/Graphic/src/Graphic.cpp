#include "Graphic.hpp"
#include "raylib.h"

void Graphic::startup()
{
    InitWindow(_width, _height, _title.c_str());
    SetTargetFPS(60);
}

void Graphic::update(float deltaTime)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}

void Graphic::shutdown()
{
    CloseWindow();
}
