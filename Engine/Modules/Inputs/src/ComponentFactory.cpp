#include "Inputs.hpp"

void Inputs::registerComponentFactory(ComponentFactory& componentFactory)
{
    componentFactory.registerComponent(
        "Input", [](Entity entity, const nlohmann::json& data, Registry& registry)
        { registry.addComponent<Components::Input>(entity, data["inputConfigID"].get<int>()); });
}
