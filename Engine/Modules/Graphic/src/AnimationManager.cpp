#include "AnimationManager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

void AnimationManager::loadAnimation(int animationID, std::vector<AnimationFrame> frames)
{
    animations[animationID] = frames;
}

void AnimationManager::loadAnimations(std::string filePath)
{
    std::ifstream file(filePath);
    nlohmann::json data;
    file >> data;

    const auto& animationsData = data["animations"];

    for (const auto& animationData : animationsData)
    {
        int animationID = animationData["animationID"].get<int>();
        std::vector<AnimationFrame> frames;

        for (const auto& frameData : animationData["frames"])
        {
            frames.push_back({frameData["textureID"].get<int>(), frameData["width"].get<int>(),
                              frameData["height"].get<int>(), frameData["originX"].get<int>(),
                              frameData["originY"].get<int>()});
        }

        loadAnimation(animationID, frames);
    }
}

void AnimationManager::removeAnimation(int animationID)
{
    animations.erase(animationID);
}

std::vector<AnimationFrame> AnimationManager::getAnimation(int animationID)
{
    return animations[animationID];
}

void AnimationManager::playAnimation(int animationID, Components::Animation& animation)
{
    animation.animationID = animationID;
    animation.currentFrame = 0;
    animation.elapsedTime = 0;
    animation.playing = true;
}

void AnimationManager::updateAnimation(Components::Animation& animation, float deltaTime)
{
    if (animations.find(animation.animationID) == animations.end()) return;

    auto& frames = animations[animation.animationID];
    auto& currentFrame = frames[animation.currentFrame];

    animation.elapsedTime += deltaTime;
    if (animation.elapsedTime >= animation.frameTime)
    {
        animation.elapsedTime = 0;
        animation.currentFrame++;
        if (animation.currentFrame >= frames.size())
        {
            if (animation.loop)
                animation.currentFrame = 0;
            else
            {
                animation.currentFrame = frames.size() - 1;
                stopAnimation(animation);
            }
        }
    }
}

void AnimationManager::stopAnimation(Components::Animation& animation)
{
    animation.currentFrame = 0;
    animation.elapsedTime = 0;
    animation.playing = false;
}
