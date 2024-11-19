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

void Graphic::registerScriptBindings(ScriptManager& scriptManager, Registry& registry) {
    scriptManager.registerBinding("Sprite", [&registry = registry](sol::state& luaState, Entity entity) {
        luaState["getSprite"] = [&registry, &luaState, entity]() {
            auto* sprite = registry.getComponent<Components::Sprite>(entity);
            if (!sprite)
                throw std::runtime_error("Sprite component not found");
            return luaState.create_table_with(
                "textureID", sprite->textureID,
                "width", sprite->width,
                "height", sprite->height,
                "originX", sprite->originX,
                "originY", sprite->originY
            );
        };

        luaState["setSprite"] = [&registry, &luaState, entity](sol::table data) {
            auto* sprite = registry.getComponent<Components::Sprite>(entity);
            if (!sprite)
                throw std::runtime_error("Sprite component not found");
            if (sprite) {
                sprite->textureID = data["textureID"].get_or(sprite->textureID);
                sprite->width = data["width"].get_or(sprite->width);
                sprite->height = data["height"].get_or(sprite->height);
                sprite->originX = data["originX"].get_or(sprite->originX);
                sprite->originY = data["originY"].get_or(sprite->originY);
            }
        };
    });

    scriptManager.registerBinding("Position", [&registry = registry](sol::state& luaState, Entity entity) {
        luaState["getPosition"] = [&registry, &luaState, entity]() {
            auto* position = registry.getComponent<Components::Position>(entity);
            if (!position)
                throw std::runtime_error("Position component not found");
            return luaState.create_table_with(
                "x", position->x,
                "y", position->y,
                "z", position->z
            );
        };

        luaState["setPosition"] = [&registry, &luaState, entity](sol::table data) {
            auto* position = registry.getComponent<Components::Position>(entity);
            if (!position)
                throw std::runtime_error("Position component not found");
            if (position) {
                position->x = data["x"].get_or(position->x);
                position->y = data["y"].get_or(position->y);
                position->z = data["z"].get_or(position->z);
            }
        };
    });
}
