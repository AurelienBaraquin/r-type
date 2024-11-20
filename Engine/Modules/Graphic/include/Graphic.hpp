#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "ISystem.hpp"
#include "AnimationManager.hpp"
#include "SpriteManager.hpp"
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

    TextureManager& manageTextures()
    {
        return _textureManager;
    }

    SpriteManager& manageSprites()
    {
        return _spriteManager;
    }

    AnimationManager& manageAnimations()
    {
        return _animationManager;
    }    

   private:
    std::string _title;
    int _width;
    int _height;

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Event _event;

    TextureManager _textureManager;
    SpriteManager _spriteManager;
    AnimationManager _animationManager;
    std::unordered_map<int, SDL_Texture*> _textures;

    SDL_Texture* getTexture(int textureID);
    void loadTexturesInMemory();

    void drawTexture(BrutSprite* sprite, Components::Position* position);
    void drawTextureEx(BrutSprite* sprite, Components::Position* position,
                       Components::Rotation* rotation, Components::Scale* scale);
};
