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
    Graphic(std::string title, int width, int height);

    ~Graphic() override;

    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;
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

    // ILoader interface
    void load(const nlohmann::json& data) override
    {
    }
    std::vector<ILoader*> getLoaders() override
    {
        return {dynamic_cast<ILoader*>(&_TextureSystem), dynamic_cast<ILoader*>(&_SpriteSystem),
                dynamic_cast<ILoader*>(&_AnimationSystem)};
    }
    std::string getPart() override
    {
        return "graphic";
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

    void drawTexture(BrutSprite* sprite, Components::Position* position);
    void drawTextureEx(BrutSprite* sprite, Components::Position* position,
                       Components::Rotation* rotation, Components::Scale* scale);
};
