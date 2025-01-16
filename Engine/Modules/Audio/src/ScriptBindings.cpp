#include "Audio.hpp"

void Audio::registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
{
    ScriptSystem.registerBinding("Audio", [&registry = registry, this](sol::state& luaState) {
        luaState["playBackgroundMusic"] = [this](const std::string& filePath, float volume,
                                                 bool loop) {
            playBackgroundMusic(filePath, volume, loop);
        };

        luaState["stopBackgroundMusic"] = [this]() { stopBackgroundMusic(); };

        luaState["playSoundEffect"] = [this](const std::string& filePath, float volume) {
            playSoundEffect(filePath, volume);
        };
    });
}
