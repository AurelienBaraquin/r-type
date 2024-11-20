#include "Graphic.hpp"

void Graphic::registerComponentFactory(ComponentFactory& componentFactory)
{
    componentFactory.registerComponent(
        "Sprite",
        [](Entity entity, const nlohmann::json& data, Registry& registry)
        {
            registry.addComponent<Components::Sprite>(
                entity, data["spriteID"].get<int>());
        });

    componentFactory.registerComponent(
        "Animation",
        [](Entity entity, const nlohmann::json& data, Registry& registry)
        {
            registry.addComponent<Components::Animation>(
                entity, data["animationID"].get<int>(), data["currentFrame"].get<int>(),
                data["frameTime"].get<float>(), data["elapsedTime"].get<float>(),
                data["loop"].get<bool>(), data["playing"].get<bool>());
        });
}
