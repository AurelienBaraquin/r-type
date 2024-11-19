#pragma once

#include "ISystem.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.hpp"
#include <string>

#include "Transform.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"

class Graphic : public ISystem
{
   public:
    Graphic(std::string title, int width, int height) : _title(title), _width(width), _height(height)
    {
    }

    ~Graphic() override = default;

    void startup() override;
    void update(float deltaTime, Registry& registry) override;
    void shutdown() override;
    void registerScriptBindings(ScriptManager& scriptManager, Registry& registry) override;

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
    void loadTexturesInMemory();

    void drawTexture(Components::Sprite* sprite, Components::Position* position);
    void drawTextureEx(Components::Sprite* sprite, Components::Position* position, Components::Rotation* rotation, Components::Scale* scale);
};
