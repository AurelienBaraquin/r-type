#pragma once

#include "Sprite.hpp"
#include <unordered_map>

class SpriteManager {
public:
    void loadSprite(int spriteID, int textureID, float width, float height, float originX, float originY);
    void removeSprite(int spriteID);
    Components::Sprite getSprite(int spriteID);

private:
    std::unordered_map<int, Components::Sprite> sprites;
};
