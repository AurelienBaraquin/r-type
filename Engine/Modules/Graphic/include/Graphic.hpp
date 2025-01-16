#pragma once

#include "RaylibConfig.hpp"

#include <string>
#include <tuple>
#include <vector>

#include "AnimationSystem.hpp"
#include "ISystem.hpp"
#include "SpriteSystem.hpp"
#include "TextureSystem.hpp"
#include "Transform.hpp"

class Graphic : public ISystem, public ILoader, public NotThreadable
{
   public:
    Graphic(const std::string& title, int width, int height);

    ~Graphic() override;

    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;
    void registerScriptBindings(ScriptSystem& scriptSystem, Registry& registry) override;
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

    void drawTexture(BrutSprite* sprite, Components::Position* position);
    void drawTextureEx(BrutSprite* sprite, Components::Position* position,
                       Components::Rotation* rotation, Components::Scale* scale);

   private:
    Camera2D camera = {0};
    std::string _title;
    int _width;
    int _height;
    std::tuple<int, int> _mousePosition;

    TextureSystem _TextureSystem;
    SpriteSystem _SpriteSystem;
    AnimationSystem _AnimationSystem;
};
