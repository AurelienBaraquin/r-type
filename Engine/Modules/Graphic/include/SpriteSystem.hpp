#pragma once

#include <unordered_map>
#include <vector>

#include "Loader.hpp"
#include "Sprite.hpp"

class SpriteSystem : public ILoader
{
   public:
    void loadSprite(int spriteID, int textureID, int width, int height, int originX, int originY);

    // Loader interface
    void load(const nlohmann::json& data) override;
    std::string getPart() override { return "sprites"; }

    void removeSprite(int spriteID);
    BrutSprite getSprite(int spriteID);

   private:
    std::unordered_map<int, BrutSprite> sprites;
};
