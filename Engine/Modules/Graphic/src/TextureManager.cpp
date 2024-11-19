#include "TextureManager.hpp"

void TextureManager::loadTexture(int textureID, const unsigned char* data, std::size_t size)
{
    textures[textureID] = Texture{data, size};
}

void TextureManager::removeTexture(int textureID)
{
    textures.erase(textureID);
}

const Texture& TextureManager::getTexture(int textureID)
{
    return textures[textureID];
}
