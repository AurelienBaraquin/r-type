#include "Audio.hpp"

#include <iostream>
#include <stdexcept>

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::playBackgroundMusic(const std::string& filePath, float volume)
{
    if (!music.openFromFile(filePath)) {
        std::cerr << "Failed to load background music: " << filePath << std::endl;
        return;
    }

    music.setVolume(volume);
    music.setLoop(true);
    music.play();
}

void Audio::stopBackgroundMusic()
{
    music.stop();
    std::cout << "Background music stopped!" << std::endl;
}

void Audio::playSoundEffect(const std::string& filePath, float volume)
{
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "Failed to load sound effect: " << filePath << std::endl;
        return;
    }

    sound.setBuffer(buffer);
    sound.setVolume(volume);
    sound.play();
}

void Audio::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    for (auto entity : registry.view<AudioSource>()) {
        auto* audioSource = registry.getComponent<AudioSource>(entity);

        if (audioSource && audioSource->playOnUpdate) {
            playSoundEffect(audioSource->filePath, audioSource->volume);
            audioSource->playOnUpdate = false;
        }
    }
}
