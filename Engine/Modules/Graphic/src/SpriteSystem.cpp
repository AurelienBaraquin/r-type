#include "SpriteSystem.hpp"

void SpriteSystem::loadSprite(int spriteID, int textureID, int width, int height, int originX,
                              int originY)
{
    sprites[spriteID] = {textureID, width, height, originX, originY};
}

void SpriteSystem::load(const nlohmann::json& data)
{
    for (const auto& spriteData : data) {
        int spriteID = spriteData["spriteID"].get<int>();

        const auto& data = spriteData["data"];

        int textureID = data["textureID"].get<int>();
        int width = data["width"].get<int>();
        int height = data["height"].get<int>();
        int originX = data["originX"].get<int>();
        int originY = data["originY"].get<int>();

        loadSprite(spriteID, textureID, width, height, originX, originY);
    }
}

void SpriteSystem::removeSprite(int spriteID)
{
    sprites.erase(spriteID);
}

BrutSprite SpriteSystem::getSprite(int spriteID)
{
    return sprites[spriteID];
}
