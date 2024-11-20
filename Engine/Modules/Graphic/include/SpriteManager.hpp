#pragma once

#include <unordered_map>
#include <vector>

#include "Sprite.hpp"

class SpriteManager
{
   public:
    void loadSprite(int spriteID, int textureID, int width, int height, int originX, int originY);
    void removeSprite(int spriteID);
    BrutSprite getSprite(int spriteID);

   private:
    std::unordered_map<int, BrutSprite> sprites;
};
