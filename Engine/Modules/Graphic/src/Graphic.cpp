#include "Graphic.hpp"

#include <algorithm>
#include <stdexcept>

#include "Sprite.hpp"
#include "Transform.hpp"

Graphic::Graphic(const std::string& title, int width, int height)
    : _title(title), _width(width), _height(height)
{
    InitWindow(_width, _height, _title.c_str());
    std::cout << "Graphic module initialized" << std::endl;
    SetTargetFPS(60);
    // camera.offset = (Vector2){ width/2.0f, height/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;
}

void Graphic::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    if (WindowShouldClose()) {
        eventManager->publish(std::make_shared<Events::Shutdown>());
        return;
    }
    std::cout << "Graphic: Update\n";
    RegistryLock lock(registry);

    std::vector<Entity> entitiesToDraw;
    std::cout << "Graphic: Drawing entities\n";
    auto f = async([this, &registry, deltaTime, &entitiesToDraw]() {
        for (auto entity : registry.view<Components::Sprite, Components::Position,
                                         Components::Scale, Components::Rotation>()) {
            entitiesToDraw.push_back(entity);
        }
        for (auto entity : registry.view<Components::Animation, Components::Position,
                                         Components::Scale, Components::Rotation>()) {
            entitiesToDraw.push_back(entity);
        }

        std::sort(entitiesToDraw.begin(), entitiesToDraw.end(), [&registry](Entity a, Entity b) {
            auto positionA = registry.getComponent<Components::Position>(a);
            auto positionB = registry.getComponent<Components::Position>(b);
            if (!positionA || !positionB) {
                throw std::runtime_error("Position component not found");
            }
            return positionA->z < positionB->z;
        });
    });

    BeginDrawing();
    std::cout << "Graphic: Drawing\n";
    BeginMode2D(camera);
    std::cout << "Graphic: Drawing mode 2D\n";
    ClearBackground(BLACK);
    std::cout << "Graphic: Clear background\n";
    f.wait();
    std::cout << "Graphic: Drawing entities\n";
    for (auto entity : entitiesToDraw) {
        if (registry.hasComponent<Components::Animation>(entity)) {
            std::cout << "Graphic: Drawing animation\n";
            auto animation = registry.getComponent<Components::Animation>(entity);
            auto position = registry.getComponent<Components::Position>(entity);
            auto scale = registry.getComponent<Components::Scale>(entity);
            auto rotation = registry.getComponent<Components::Rotation>(entity);
            if (!animation || !position || !scale || !rotation) {
                continue;
            }
            std::cout << "Graphic: Drawing all animation\n";
            _AnimationSystem.updateAnimation(*animation, deltaTime);

            if (!animation->playing) continue;

            auto frames = _AnimationSystem.getAnimation(animation->animationID);
            auto currentFrame = frames[animation->currentFrame];

            auto sprite =
                BrutSprite{currentFrame.textureID, currentFrame.width, currentFrame.height,
                           currentFrame.originX, currentFrame.originY};

            drawTextureEx(&sprite, position, rotation, scale);
        } else if (registry.hasComponent<Components::Sprite>(entity)) {
            std::cout << "Graphic: Drawing sprite\n";
            auto sprite = registry.getComponent<Components::Sprite>(entity);
            auto position = registry.getComponent<Components::Position>(entity);
            auto scale = registry.getComponent<Components::Scale>(entity);
            auto rotation = registry.getComponent<Components::Rotation>(entity);
            std::cout << "Graphic: Drawing all sprite\n";
            if (!sprite || !position || !scale || !rotation) {
                continue;
            }
            auto brutSprite = _SpriteSystem.getSprite(sprite->spriteID);
            drawTextureEx(&brutSprite, position, rotation, scale);
            std::cout << "Graphic: Drawing sprite end\n";
        }
    }
    std::cout << "Graphic: End drawing\n";
    EndDrawing();
}

Graphic::~Graphic()
{
    CloseWindow();
}

void Graphic::drawTexture(BrutSprite* sprite, Components::Position* position)
{
    auto texture = _TextureSystem.get(sprite->textureID);

    if (texture.id == 0) {
        Logger::getInstance().error("Texture not found: " + std::to_string(sprite->textureID));
        return;
    }

    DrawTexture(texture, static_cast<int>(position->x), static_cast<int>(position->y), WHITE);
}

void Graphic::drawTextureEx(BrutSprite* sprite, Components::Position* position,
                            Components::Rotation* rotation, Components::Scale* scale)
{
    auto texture = _TextureSystem.get(sprite->textureID);

    if (texture.id == 0) {
        Logger::getInstance().error("Texture not found: " + std::to_string(sprite->textureID));
        return;
    }

    Vector2 origin = {static_cast<float>(sprite->originX), static_cast<float>(sprite->originY)};
    Vector2 pos = {static_cast<float>(position->x), static_cast<float>(position->y)};
    float width = (scale->x > 0) ? scale->x : sprite->width;
    float height = (scale->y > 0) ? scale->y : sprite->height;

    DrawTexturePro(texture, {origin.x, origin.y, width, height}, {pos.x, pos.y, width, height}, {0},
                   rotation->angle, WHITE);
}
