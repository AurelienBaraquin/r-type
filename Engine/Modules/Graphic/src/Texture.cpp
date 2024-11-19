#include "Graphic.hpp"
#include <stdexcept>

SDL_Texture* LoadTextureFromMemory(SDL_Renderer* renderer, const unsigned char* data, size_t size) {
    SDL_RWops* rw = SDL_RWFromConstMem(data, static_cast<int>(size));
    if (!rw)
        return nullptr;

    SDL_Surface* surface = IMG_Load_RW(rw, 1);
    if (!surface)
        return nullptr;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void Graphic::loadTexture(int textureID, const unsigned char* data, std::size_t size) {
    _textureManager.loadTexture(textureID, data, size);
}

void Graphic::loadTexturesInMemory() {
    for (auto& texture : _textureManager) {
        _textures[texture.first] = LoadTextureFromMemory(_renderer, texture.second.data, texture.second.size);
        if (!_textures[texture.first]) {
            throw std::runtime_error("Failed to load texture from memory: " + std::string(IMG_GetError()));
        }
    }
}

void Graphic::removeTexture(int textureID) {
    _textureManager.removeTexture(textureID);
    SDL_DestroyTexture(_textures[textureID]);
    _textures.erase(textureID);
}

SDL_Texture* Graphic::getTexture(int textureID) {
    return _textures[textureID];
}

void Graphic::drawTexture(int textureID, float width, float height, float x, float y) {
    SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
    SDL_RenderCopy(_renderer, getTexture(textureID), nullptr, &rect);
}
