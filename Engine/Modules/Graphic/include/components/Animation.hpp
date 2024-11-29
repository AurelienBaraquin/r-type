#pragma once

namespace Components {
struct Animation {
    int animationID;
    int currentFrame;
    float elapsedTime;
    bool loop;
    bool playing;

    int baseAnimationID = animationID;
};
}  // namespace Components
