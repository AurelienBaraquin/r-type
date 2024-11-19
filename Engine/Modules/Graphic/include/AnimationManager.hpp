#pragma once

#include "Animation.hpp"
#include "Sprite.hpp"
#include <vector>
#include <unordered_map>

using AnimationFrame = Components::Sprite;

class AnimationManager {
public:
    void loadAnimation(int animationID, std::vector<AnimationFrame> frames);
    void removeAnimation(int animationID);
    std::vector<AnimationFrame> getAnimation(int animationID);

    void playAnimation(int animationID, Components::Animation& animation);
    void updateAnimation(Components::Animation& animation, float deltaTime);
    void stopAnimation(Components::Animation& animation);

private:
    std::unordered_map<int, std::vector<AnimationFrame>> animations;
};
