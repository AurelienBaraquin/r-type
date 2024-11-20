#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Animation.hpp"
#include "Sprite.hpp"

#include "Loader.hpp"

using AnimationFrame = BrutSprite;

class AnimationSystem : public ILoader
{
   public:
    void loadAnimation(int animationID, std::vector<AnimationFrame> frames);

    // Loader interface
    void load(std::string filePath) override;

    void removeAnimation(int animationID);
    std::vector<AnimationFrame> getAnimation(int animationID);

    void playAnimation(int animationID, Components::Animation& animation);
    void updateAnimation(Components::Animation& animation, float deltaTime);
    void stopAnimation(Components::Animation& animation);

   private:
    std::unordered_map<int, std::vector<AnimationFrame>> animations;
};
