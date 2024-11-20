#include "SpriteSystem.hpp"

void SpriteSystem::loadSprite(int spriteID, int textureID, int width, int height, int originX,
                              int originY)
{
    sprites[spriteID] = {textureID, width, height, originX, originY};
}

void SpriteSystem::removeSprite(int spriteID)
{
    sprites.erase(spriteID);
}

BrutSprite SpriteSystem::getSprite(int spriteID)
{
    return sprites[spriteID];
}
