#include <stdexcept>

#include "Graphic.hpp"

SDL_Texture* LoadTextureFromMemory(SDL_Renderer* renderer, const unsigned char* data, size_t size)
{
    SDL_RWops* rw = SDL_RWFromConstMem(data, static_cast<int>(size));
    if (!rw) return nullptr;

    SDL_Surface* surface = IMG_Load_RW(rw, 1);
    if (!surface) return nullptr;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void Graphic::loadTexturesInMemory()
{
    for (auto& texture : _textureManager)
    {
        _textures[texture.first] =
            LoadTextureFromMemory(_renderer, texture.second.data, texture.second.size);
        if (!_textures[texture.first])
        {
            throw std::runtime_error("Failed to load texture from memory: " +
                                     std::string(IMG_GetError()));
        }
    }
}

SDL_Texture* Graphic::getTexture(int textureID)
{
    return _textures[textureID];
}

void Graphic::drawTexture(BrutSprite* sprite, Components::Position* position)
{
    SDL_Rect srcRect = {
        sprite->originX,
        sprite->originY,
        sprite->width,
        sprite->height
    };

    SDL_Rect dstRect = {static_cast<int>(position->x), static_cast<int>(position->y), sprite->width,
                        sprite->height};

    SDL_Texture* texture = getTexture(sprite->textureID);
    if (!texture) return;

    SDL_RenderCopy(_renderer, texture, &srcRect, &dstRect);
}

void Graphic::drawTextureEx(BrutSprite* sprite, Components::Position* position,
                            Components::Rotation* rotation, Components::Scale* scale)
{


    SDL_Rect srcRect = {
        sprite->originX,
        sprite->originY,
        sprite->width,
        sprite->height
    };

    SDL_Rect dstRect = {
        static_cast<int>(position->x), static_cast<int>(position->y),
        static_cast<int>(sprite->width * scale->x),
        static_cast<int>(sprite->height * scale->y)
    };

    SDL_Point center = {
        dstRect.w / 2,
        dstRect.h / 2
    };

    SDL_Texture* texture = getTexture(sprite->textureID);
    if (!texture)
    {
        return;
    }

    SDL_RenderCopyEx(_renderer, texture, &srcRect, &dstRect,
                     rotation->angle,
                     &center,
                     SDL_FLIP_NONE
    );
}
