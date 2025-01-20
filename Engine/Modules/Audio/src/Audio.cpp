#include "Audio.hpp"

#include <iostream>
#include <stdexcept>

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

AudioManager::AudioManager()
{
    InitAudioDevice();
}

AudioManager::~AudioManager()
{
    for (auto& [path, sound] : soundCache) {
        UnloadSound(sound);
    }
    for (auto& [path, music] : musicCache) {
        UnloadMusicStream(music);
    }
    CloseAudioDevice();
}

Sound AudioManager::loadSound(const std::string& filePath)
{
    if (soundCache.find(filePath) == soundCache.end()) {
        soundCache[filePath] = LoadSound(filePath.c_str());
    }
    return soundCache[filePath];
}

void AudioManager::unloadSound(const std::string& filePath)
{
    if (soundCache.find(filePath) != soundCache.end()) {
        UnloadSound(soundCache[filePath]);
        soundCache.erase(filePath);
    }
}

Music AudioManager::loadMusic(const std::string& filePath)
{
    if (musicCache.find(filePath) == musicCache.end()) {
        musicCache[filePath] = LoadMusicStream(filePath.c_str());
    }
    return musicCache[filePath];
}

void AudioManager::unloadMusic(const std::string& filePath)
{
    if (musicCache.find(filePath) != musicCache.end()) {
        UnloadMusicStream(musicCache[filePath]);
        musicCache.erase(filePath);
    }
}

Audio::Audio()
{
}

Audio::~Audio()
{
    if (musicPlaying) {
        StopMusicStream(currentMusic);
    }
}

void Audio::playBackgroundMusic(const std::string& filePath, float volume, bool loop)
{
    if (musicPlaying) {
        StopMusicStream(currentMusic);
    }
    currentMusic = AudioManager::getInstance().loadMusic(filePath);
    SetMusicVolume(currentMusic, volume);
    currentMusic.looping = loop;
    PlayMusicStream(currentMusic);
    musicPlaying = true;
}

void Audio::stopBackgroundMusic()
{
    if (musicPlaying) {
        StopMusicStream(currentMusic);
        musicPlaying = false;
    }
}

void Audio::playSoundEffect(const std::string& filePath, float volume)
{
    Sound sound = AudioManager::getInstance().loadSound(filePath);
    SetSoundVolume(sound, volume);
    PlaySound(sound);
}

void Audio::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
{
    if (musicPlaying) {
        UpdateMusicStream(currentMusic);
    }

    RegistryLock lock(registry);
    for (auto entity : registry.view<AudioSource>()) {
        auto* audioSource = registry.getComponent<AudioSource>(entity);

        if (audioSource && audioSource->playOnUpdate) {
            playSoundEffect(audioSource->filePath, audioSource->volume);
            audioSource->playOnUpdate = false;
        }
    }
}
