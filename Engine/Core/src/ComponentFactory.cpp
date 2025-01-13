#include "Core.hpp"
#include "Transform.hpp"

void Engine::registerComponentFactory(ComponentFactory& componentFactory)
{
    componentFactory.registerComponent(
        "Position", [](Entity entity, const nlohmann::json& data, Registry& registry) {
            registry.addComponent<Components::Position>(entity, data["x"].get<int>(),
                                                        data["y"].get<int>(), data["z"].get<int>());
        });

    componentFactory.registerComponent(
        "Scale", [](Entity entity, const nlohmann::json& data, Registry& registry) {
            registry.addComponent<Components::Scale>(entity, data["x"].get<int>(),
                                                     data["y"].get<int>());
        });

    componentFactory.registerComponent(
        "Rotation", [](Entity entity, const nlohmann::json& data, Registry& registry) {
            registry.addComponent<Components::Rotation>(entity, data["angle"].get<float>());
        });

    componentFactory.registerComponent("Script", [](Entity entity, const nlohmann::json& data,
                                                    Registry& registry) {
        registry.addComponent<Components::Script>(entity, data["scriptPath"].get<std::string>());
    });

    componentFactory.registerComponent("Json", [](Entity entity, const nlohmann::json& data,
                                                 Registry& registry) {
        registry.addComponent<Components::Json>(entity, data);
    });
}
