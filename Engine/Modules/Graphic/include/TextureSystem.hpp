#pragma once

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureSystem
{
   public:
    void setRenderer(SDL_Renderer* renderer)
    {
        _renderer = renderer;
    }

    void load(int textureID, const std::string path);
    void remove(int textureID);
    SDL_Texture* get(int textureID) const;

    void loadTexturesInRenderer();

   private:
    std::unordered_map<int, SDL_Texture*> textures;
    SDL_Renderer* _renderer;
};
