#include "Graphic.hpp"

#include <stdexcept>

#include "Sprite.hpp"
#include "Transform.hpp"

Graphic::Graphic(std::string title, int width, int height)
    : _title(title), _width(width), _height(height)
{
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
    RegistryLock lock(registry);

    std::future<std::vector<Entity>> entitiesToDrawFutur = async([&registry = registry]() {
        std::vector<Entity> entities;
        for (auto entity : registry.view<Components::Sprite, Components::Position,
                                         Components::Scale, Components::Rotation>()) {
            entities.push_back(entity);
        }
        for (auto entity : registry.view<Components::Animation, Components::Position,
                                         Components::Scale, Components::Rotation>()) {
            entities.push_back(entity);
        }
        std::sort(entities.begin(), entities.end(), [&registry](Entity a, Entity b) {
            auto positionA = registry.getComponent<Components::Position>(a);
            auto positionB = registry.getComponent<Components::Position>(b);
            return positionA->z < positionB->z;
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

    for (auto entity : entitiesToDraw) {
        if (registry.hasComponent<Components::Animation>(entity)) {
            auto animation = registry.getComponent<Components::Animation>(entity);
            auto position = registry.getComponent<Components::Position>(entity);
            auto scale = registry.getComponent<Components::Scale>(entity);
            auto rotation = registry.getComponent<Components::Rotation>(entity);

            _AnimationSystem.updateAnimation(*animation, deltaTime);

            if (!animation->playing) continue;

            auto frames = _AnimationSystem.getAnimation(animation->animationID);
            auto currentFrame = frames[animation->currentFrame];

            auto sprite =
                BrutSprite{currentFrame.textureID, currentFrame.width, currentFrame.height,
                           currentFrame.originX, currentFrame.originY};

            drawTextureEx(&sprite, position, rotation, scale);
        } else if (registry.hasComponent<Components::Sprite>(entity)) {
            auto sprite = registry.getComponent<Components::Sprite>(entity);
            auto position = registry.getComponent<Components::Position>(entity);
            auto scale = registry.getComponent<Components::Scale>(entity);
            auto rotation = registry.getComponent<Components::Rotation>(entity);

            auto brutSprite = _SpriteSystem.getSprite(sprite->spriteID);

            drawTextureEx(&brutSprite, position, rotation, scale);
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