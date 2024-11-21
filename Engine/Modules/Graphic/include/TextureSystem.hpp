#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Loader.hpp>
#include <string>
#include <unordered_map>

class TextureSystem : public ILoader
{
   public:
    void setRenderer(SDL_Renderer* renderer)
    {
        _renderer = renderer;
    }

    void loadTexture(int textureID, const std::string path);

    // Loader interface
    void load(const nlohmann::json& data) override;
    std::string getPart() override
    {
        return "textures";
    }

    void remove(int textureID);
    SDL_Texture* get(int textureID) const;

    void loadTexturesInRenderer();

   private:
    std::unordered_map<int, SDL_Texture*> textures;
    SDL_Renderer* _renderer;
};
