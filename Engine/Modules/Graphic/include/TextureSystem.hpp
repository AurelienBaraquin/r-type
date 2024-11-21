#pragma once

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Loader.hpp>

class TextureSystem : public ILoader
{
   public:
    void setRenderer(SDL_Renderer* renderer)
    {
        _renderer = renderer;
    }

    void loadTexture(int textureID, const std::string path);
    void load(const std::string& filePath) override;
    void remove(int textureID);
    SDL_Texture* get(int textureID) const;

    void loadTexturesInRenderer();

   private:
    std::unordered_map<int, SDL_Texture*> textures;
    SDL_Renderer* _renderer;
};
