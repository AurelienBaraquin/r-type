#include "SpriteManager.hpp"

void SpriteManager::loadSprite(int spriteID, int textureID, float width, float height, float originX, float originY)
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
