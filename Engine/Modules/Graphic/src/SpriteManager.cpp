#include "SpriteManager.hpp"

void SpriteManager::loadSprite(int spriteID, int textureID, int width, int height, int originX, int originY)
{
    sprites[spriteID] = {textureID, width, height, originX, originY};
}

void SpriteManager::removeSprite(int spriteID)
{
    sprites.erase(spriteID);
}

BrutSprite SpriteManager::getSprite(int spriteID)
{
    return sprites[spriteID];
}
