#include "Graphic.hpp"

#include <stdexcept>

#include "Sprite.hpp"
#include "Transform.hpp"

Graphic::Graphic(std::string title, int width, int height)
    : _title(title), _width(width), _height(height)
{
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) & IMG_INIT_PNG)) {
        throw std::runtime_error("Failed to initialize SDL_image: " + std::string(IMG_GetError()));
    }

    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _width, _height, SDL_WINDOW_SHOWN);
    if (!_window) {
        throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }

    _TextureSystem.setRenderer(_renderer);
}
void Graphic::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    struct EntityRenderData {
        Entity entity;
        bool hasAnimation;
        std::unique_ptr<Components::Position> position;
        std::unique_ptr<Components::Scale> scale;
        std::unique_ptr<Components::Rotation> rotation;
        std::unique_ptr<Components::Animation> animation;
        std::unique_ptr<Components::Sprite> sprite;
    };

    std::future<std::vector<EntityRenderData>> entitiesToDrawFutur = async([&registry]() {
        RegistryLock lock(registry);
        std::vector<EntityRenderData> entities;

        auto addEntity = [&](Entity entity) {
            EntityRenderData data;
            data.entity = entity;
            data.hasAnimation = registry.hasComponent<Components::Animation>(entity);
            data.position = std::make_unique<Components::Position>(*registry.getComponent<Components::Position>(entity));
            data.scale = std::make_unique<Components::Scale>(*registry.getComponent<Components::Scale>(entity));
            data.rotation = std::make_unique<Components::Rotation>(*registry.getComponent<Components::Rotation>(entity));

            if (data.hasAnimation) {
                data.animation = std::make_unique<Components::Animation>(*registry.getComponent<Components::Animation>(entity));
            } else {
                data.sprite = std::make_unique<Components::Sprite>(*registry.getComponent<Components::Sprite>(entity));
            }

            entities.push_back(std::move(data));
        };

        for (auto entity : registry.view<Components::Sprite, Components::Position, Components::Scale, Components::Rotation>()) {
            addEntity(entity);
        }
        for (auto entity : registry.view<Components::Animation, Components::Position, Components::Scale, Components::Rotation>()) {
            addEntity(entity);
        }

        std::sort(entities.begin(), entities.end(), [](const EntityRenderData& a, const EntityRenderData& b) {
            return a.position->z < b.position->z;
        });

        return entities;
    });

    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            eventManager->publish<Events::Shutdown>(std::make_shared<Events::Shutdown>());
        }
        if (_event.type == SDL_KEYDOWN) {
            if (_event.key.keysym.sym == SDLK_ESCAPE) {
                eventManager->publish<Events::Shutdown>(std::make_shared<Events::Shutdown>());
            }
        }
        if (_event.type == SDL_MOUSEMOTION) {
            _mousePosition = std::make_tuple(_event.motion.x, _event.motion.y);
        }
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    auto entitiesToDraw = entitiesToDrawFutur.get();

    for (auto& entityData : entitiesToDraw) {
        if (entityData.hasAnimation) {
            _AnimationSystem.updateAnimation(*entityData.animation, deltaTime);

            if (!entityData.animation->playing) continue;

            auto frames = _AnimationSystem.getAnimation(entityData.animation->animationID);
            auto currentFrame = frames[entityData.animation->currentFrame];
            auto sprite = BrutSprite{currentFrame.textureID, currentFrame.width, currentFrame.height, currentFrame.originX, currentFrame.originY};
            drawTextureEx(&sprite, entityData.position.get(), entityData.rotation.get(), entityData.scale.get());
        } else {
            auto brutSprite = _SpriteSystem.getSprite(entityData.sprite->spriteID);
            drawTextureEx(&brutSprite, entityData.position.get(), entityData.rotation.get(), entityData.scale.get());
        }
    }

    SDL_RenderPresent(_renderer);
}

Graphic::~Graphic()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window) {
        SDL_DestroyWindow(_window);
    }

    IMG_Quit();
    SDL_Quit();
}
