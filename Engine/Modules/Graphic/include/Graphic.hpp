#pragma once

#include "ISystem.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.hpp"
#include <string>

class Graphic : public ISystem
{
   public:
    Graphic(std::string title, int width, int height) : _title(title), _width(width), _height(height)
    {
    }

    ~Graphic() override = default;

    void startup() override;
    void update(float deltaTime) override;
    void shutdown() override;

    void loadTexture(int textureID, const unsigned char* data, std::size_t size);
    void removeTexture(int textureID);

   private:
    std::string _title;
    int _width;
    int _height;

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Event _event;

    TextureManager _textureManager;
    std::unordered_map<int, SDL_Texture*> _textures;

    SDL_Texture* getTexture(int textureID);
    void loadTexturesInMemory(int textureID, const unsigned char* data, std::size_t size);

    void drawTexture(int textureID, float width, float height, float x, float y);
};
