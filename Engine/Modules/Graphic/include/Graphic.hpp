#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "AnimationManager.hpp"
#include "ISystem.hpp"
#include "Sprite.hpp"
#include "TextureManager.hpp"
#include "Transform.hpp"

class Graphic : public ISystem
{
   public:
    Graphic(std::string title, int width, int height)
        : _title(title), _width(width), _height(height)
    {
    }

    ~Graphic() override = default;

    void startup() override;
    void update(float deltaTime, Registry& registry) override;
    void shutdown() override;
    void registerScriptBindings(ScriptManager& scriptManager, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

    void loadTexture(int textureID, const unsigned char* data, std::size_t size);
    void removeTexture(int textureID);

    void loadAnimation(int animationID, std::vector<AnimationFrame> frames);
    void removeAnimation(int animationID);

   private:
    std::string _title;
    int _width;
    int _height;

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Event _event;

    TextureManager _textureManager;
    AnimationManager _animationManager;
    std::unordered_map<int, SDL_Texture*> _textures;

    SDL_Texture* getTexture(int textureID);
    void loadTexturesInMemory();

    void drawTexture(Components::Sprite* sprite, Components::Position* position);
    void drawTextureEx(Components::Sprite* sprite, Components::Position* position,
                       Components::Rotation* rotation, Components::Scale* scale);
};
