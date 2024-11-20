#pragma once

#include <unordered_map>
#include <vector>

#include "Sprite.hpp"

#include "Loader.hpp"

class SpriteSystem : public ILoader
{
   public:
    void loadSprite(int spriteID, int textureID, int width, int height, int originX, int originY);

    // Loader interface
    void load(const std::string& filePath) override;

    void removeSprite(int spriteID);
    BrutSprite getSprite(int spriteID);

   private:
    std::unordered_map<int, BrutSprite> sprites;
};
