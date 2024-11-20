//
// Created by Guillaume Tran on 20/11/2024.
//

#include "Physics.hpp"
#include "BoxCollider.hpp"

void Physics::registerComponentFactory(ComponentFactory& componentFactory)
{
    componentFactory.registerComponent(
            "BoxCollider",
            [this](Entity entity, const nlohmann::json& data, Registry& registry)
            {
                struct Components::BoxCollider boxCollider;

                boxCollider.width = data["width"].get<float>();
                boxCollider.height = data["height"].get<float>();
                boxCollider.body = cpBodyNew(1.0f, cpMomentForBox(1.0f, boxCollider.width, boxCollider.height));
                boxCollider.shape = cpBoxShapeNew(boxCollider.body, boxCollider.width, boxCollider.height, 0.0f);
                cpSpaceAddBody(_space, boxCollider.body);
                cpSpaceAddShape(_space, boxCollider.shape);

                registry.addComponent<Components::BoxCollider>(
                        entity, boxCollider);
            }
    );
}
