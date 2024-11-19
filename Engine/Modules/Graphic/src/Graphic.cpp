#include "Graphic.hpp"
#include <stdexcept>

#include "Sprite.hpp"
#include "Transform.hpp"

void Graphic::startup() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) & IMG_INIT_PNG)) {
        throw std::runtime_error("Failed to initialize SDL_image: " + std::string(IMG_GetError()));
    }

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width,
        _height,
        SDL_WINDOW_SHOWN
    );
    if (!_window) {
        throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }

    loadTexturesInMemory();
}

void Graphic::update(float deltaTime, Registry& registry) {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            exit(0); // TODO
        }
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    for (auto entity : registry.view<Components::Sprite, Components::Position, Components::Scale, Components::Rotation>()) {
        auto sprite = registry.getComponent<Components::Sprite>(entity);
        auto position = registry.getComponent<Components::Position>(entity);
        auto scale = registry.getComponent<Components::Scale>(entity);
        auto rotation = registry.getComponent<Components::Rotation>(entity);

        drawTextureEx(sprite, position, rotation, scale);
    }

    SDL_RenderPresent(_renderer);
}

void Graphic::shutdown() {
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window) {
        SDL_DestroyWindow(_window);
    }

    IMG_Quit();
    SDL_Quit();
}
