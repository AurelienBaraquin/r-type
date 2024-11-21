#include "TextureSystem.hpp"
#include <stdexcept>
#include "Log.hpp"

void TextureSystem::loadTexture(int textureID, const std::string path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
    {
        Logger::getInstance().error("Failed to load texture: " + std::string(IMG_GetError()));
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        Logger::getInstance().error("Failed to create texture: " + std::string(SDL_GetError()));
        return;
    }

    textures[textureID] = texture;
}

void TextureSystem::load(const nlohmann::json& data)
{
    for (const auto& textureData : data)
    {
        int textureID = textureData["textureID"].get<int>();
        std::string path = textureData["path"].get<std::string>();

        loadTexture(textureID, path);
    }
}

void TextureSystem::remove(int textureID)
{
    auto it = textures.find(textureID);
    if (it != textures.end())
    {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
    }
}

SDL_Texture* TextureSystem::get(int textureID) const
{
    auto it = textures.find(textureID);
    if (it != textures.end())
    {
        return it->second;
    }
    return nullptr;
}
