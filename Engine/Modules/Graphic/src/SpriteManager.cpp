#include "SpriteManager.hpp"

void SpriteManager::loadSprite(int spriteID, int textureID, int width, int height, int originX, int originY)
{
    sprites[spriteID] = Components::Sprite{textureID, width, height, originX, originY};
}

void SpriteManager::removeSprite(int spriteID)
{
    sprites.erase(spriteID);
}

Components::Sprite SpriteManager::getSprite(int spriteID)
{
    return sprites[spriteID];
}
