#include "Audio.hpp"

void Audio::registerComponentFactory(ComponentFactory& componentFactory)
{
    componentFactory.registerComponent("AudioSource", [](Entity entity, const nlohmann::json& data,
                                                         Registry& registry) {
        registry.addComponent<AudioSource>(entity, data["filePath"].get<std::string>(),
                                           data["volume"].get<float>(), data["loop"].get<bool>());
    });
}
