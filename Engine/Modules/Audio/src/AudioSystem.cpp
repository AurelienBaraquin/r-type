#include "Audio.hpp"

void Audio::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    for (auto entity : registry.view<AudioSource>()) {
        auto* audioSource = registry.getComponent<AudioSource>(entity);

        if (audioSource->playOnUpdate) {
            playSoundEffect(audioSource->filePath, audioSource->volume);
            audioSource->playOnUpdate = false;
        }
    }
}
