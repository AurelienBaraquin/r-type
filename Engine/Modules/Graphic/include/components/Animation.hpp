#pragma once

namespace Components {
struct Animation {
    int animationID;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    bool loop;
    bool playing;
};
}  // namespace Components
