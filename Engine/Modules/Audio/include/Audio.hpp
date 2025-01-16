#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "ISystem.hpp"
#include "Registry.hpp"
#include "ScriptSystem.hpp"

struct AudioSource {
    std::string filePath;
    float volume = 1.0f;
    bool loop = false;
    bool playOnUpdate = false;
};

class AudioManager {
   public:
    static AudioManager& getInstance();

    Sound loadSound(const std::string& filePath);
    void unloadSound(const std::string& filePath);
    Music loadMusic(const std::string& filePath);
    void unloadMusic(const std::string& filePath);

   private:
    AudioManager();
    ~AudioManager();
    std::unordered_map<std::string, Sound> soundCache;
    std::unordered_map<std::string, Music> musicCache;
};

class Audio : public ISystem, public NotThreadable {
   public:
    Audio();
    ~Audio();

    void playBackgroundMusic(const std::string& filePath, float volume = 1.0f, bool loop = true);
    void stopBackgroundMusic();
    void playSoundEffect(const std::string& filePath, float volume = 1.0f);
    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;

    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

   private:
    Music currentMusic;
    bool musicPlaying = false;
};
