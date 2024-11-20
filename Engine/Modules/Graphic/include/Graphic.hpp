#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "AnimationSystem.hpp"
#include "ISystem.hpp"
#include "SpriteSystem.hpp"
#include "TextureSystem.hpp"
#include "Transform.hpp"

class Graphic : public ISystem, public ILoader
{
   public:
    Graphic(std::string title, int width, int height)
        : _title(title), _width(width), _height(height)
    {
    }

    ~Graphic() override = default;

    void startup() override;
    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;
    void shutdown() override;
    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

    TextureSystem& manageTextures()
    {
        return _TextureSystem;
    }

    SpriteSystem& manageSprites()
    {
        return _SpriteSystem;
    }

    AnimationSystem& manageAnimations()
    {
        return _AnimationSystem;
    }

    void load(const std::string& filePath) override
    {
        _AnimationSystem.load(filePath);
        _SpriteSystem.load(filePath);
    }

   private:
    std::string _title;
    int _width;
    int _height;

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Event _event;

    TextureSystem _TextureSystem;
    SpriteSystem _SpriteSystem;
    AnimationSystem _AnimationSystem;
    std::unordered_map<int, SDL_Texture*> _textures;

    SDL_Texture* getTexture(int textureID);
    void loadTexturesInMemory();

    void drawTexture(BrutSprite* sprite, Components::Position* position);
    void drawTextureEx(BrutSprite* sprite, Components::Position* position,
                       Components::Rotation* rotation, Components::Scale* scale);
};
