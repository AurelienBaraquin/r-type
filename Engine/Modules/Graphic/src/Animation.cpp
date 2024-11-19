#include "Graphic.hpp"

void Graphic::loadAnimation(int animationID, std::vector<AnimationFrame> frames)
{
    _animationManager.loadAnimation(animationID, frames);
}

void Graphic::removeAnimation(int animationID)
{
    _animationManager.removeAnimation(animationID);
}
