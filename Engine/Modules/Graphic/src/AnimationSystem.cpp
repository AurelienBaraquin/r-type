#include "AnimationSystem.hpp"

#include "Log.hpp"

void AnimationSystem::loadAnimation(int animationID, std::vector<AnimationFrame> frames)
{
    animations[animationID] = frames;
}

void AnimationSystem::load(const nlohmann::json& data)
{
    for (const auto& animationData : data) {
        int animationID = animationData["animationID"].get<int>();
        std::vector<AnimationFrame> frames;

        for (const auto& frameData : animationData["frames"]) {
            frames.push_back({frameData["textureID"].get<int>(), frameData["width"].get<int>(),
                              frameData["height"].get<int>(), frameData["originX"].get<int>(),
                              frameData["originY"].get<int>()});
        }

        loadAnimation(animationID, frames);
    }
}

void AnimationSystem::removeAnimation(int animationID)
{
    animations.erase(animationID);
}

std::vector<AnimationFrame> AnimationSystem::getAnimation(int animationID)
{
    return animations[animationID];
}

void AnimationSystem::playAnimation(int animationID, Components::Animation& animation)
{
    if (animation.animationID == animationID) return;
    async([this, animationID, &animation]() {
        if (animations.find(animationID) == animations.end()) {
            Logger::getInstance().error("Animation not found" + std::to_string(animationID));
            return;
        }

        animation.animationID = animationID;
        animation.currentFrame = 0;
        animation.elapsedTime = 0;
        animation.playing = true;
    });
}

void AnimationSystem::updateAnimation(Components::Animation& animation, float deltaTime)
{
    if (!animation.playing) return;
    async([this, &animation, deltaTime]() {
        if (animations.find(animation.animationID) == animations.end()) {
            Logger::getInstance().error("Animation not found" + std::to_string(animation.animationID));
            return;
        }

        auto& frames = animations[animation.animationID];
        auto& currentFrame = frames[animation.currentFrame];

        animation.elapsedTime += deltaTime;
        if (animation.elapsedTime >= animation.frameTime) {
            animation.elapsedTime = 0;
            animation.currentFrame++;
            if (animation.currentFrame >= frames.size()) {
                if (animation.baseAnimationID != animation.animationID) {
                    animation.animationID = animation.baseAnimationID;
                    return;
                }
                if (animation.loop)
                    animation.currentFrame = 0;
                else {
                    animation.currentFrame = frames.size() - 1;
                    stopAnimation(animation);
                }
            }
        }
    });
}

void AnimationSystem::stopAnimation(Components::Animation& animation)
{
    animation.currentFrame = 0;
    animation.elapsedTime = 0;
    animation.playing = false;
}
