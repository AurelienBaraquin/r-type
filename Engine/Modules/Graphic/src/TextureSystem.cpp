#include "TextureSystem.hpp"

void TextureSystem::loadTexture(int textureID, const unsigned char* data, std::size_t size)
{
    textures[textureID] = Texture{data, size};
}

void TextureSystem::removeTexture(int textureID)
{
    textures.erase(textureID);
}

const Texture& TextureSystem::getTexture(int textureID)
{
    return textures[textureID];
}
