//
// Created by Guillaume Tran on 03/01/2025.
//

#pragma once

#include <string>
#include "raylib.h"

class Entity {
public:
    Entity(std::string name, std::vector<std::string> tags, Texture2D sprite) :
        name(name), tags(tags), sprite(sprite) {}
    ~Entity() = default;
private:
    std::string name;
    std::vector<std::string> tags;
    Texture2D sprite;
};
