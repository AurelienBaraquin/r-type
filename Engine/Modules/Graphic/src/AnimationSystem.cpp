#include "AnimationSystem.hpp"

#include "Log.hpp"

void AnimationSystem::loadAnimation(int animationID, std::vector<AnimationFrame> frames,
                                    float frameTime)
{
    _animations[animationID] = {frames, frameTime};
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

        float frameTime = animationData["frameTime"].get<float>();

        loadAnimation(animationID, frames, frameTime);
    }
}

void AnimationSystem::removeAnimation(int animationID)
{
    _animations.erase(animationID);
}

std::vector<AnimationFrame> AnimationSystem::getAnimation(int animationID)
{
    return _animations[animationID].frames;
}

void AnimationSystem::playAnimation(int animationID, Components::Animation& animation)
{
    if (animation.animationID == animationID) return;
    async([this, animationID, &animation]() {
        if (_animations.find(animationID) == _animations.end()) {
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
        if (_animations.find(animation.animationID) == _animations.end()) {
            Logger::getInstance().error("Animation not found" +
                                        std::to_string(animation.animationID));
            return;
        }

        auto& frames = _animations[animation.animationID].frames;
        auto& currentFrame = frames[animation.currentFrame];

        animation.elapsedTime += deltaTime;
        if (animation.elapsedTime >= _animations[animation.animationID].frameTime) {
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
