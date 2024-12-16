#pragma once

#include <SFML/Audio.hpp>
#include <string>

#include "ISystem.hpp"
#include "Registry.hpp"
#include "ScriptSystem.hpp"
#include "ISystem.hpp"
struct AudioSource {
    std::string filePath;
    float volume = 1.0f;
    bool loop = false;
    bool playOnUpdate = false;
};

class Audio : public ISystem, public NotThreadable
{
   public:
    Audio();
    ~Audio();

    void playBackgroundMusic(const std::string& filePath, float volume = 1.0f);
    void stopBackgroundMusic();
    void playSoundEffect(const std::string& filePath, float volume = 1.0f);
    void update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem) override;

    void registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry) override;
    void registerComponentFactory(ComponentFactory& componentFactory) override;

   private:
    sf::Music music;
    sf::Sound sound;
    sf::SoundBuffer buffer;
};
