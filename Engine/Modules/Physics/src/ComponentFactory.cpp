//
// Created by Guillaume Tran on 20/11/2024.
//

#include "Area2D.hpp"
#include "BoxCollider.hpp"
#include "Physics.hpp"
void Physics::registerComponentFactory(ComponentFactory& componentFactory)
{
    componentFactory.registerComponent(
        "BoxCollider",
        [this](Entity entity, const nlohmann::json& data, Registry& registry)
        {
            struct Components::BoxCollider boxCollider;

            boxCollider.width = data["width"].get<float>();
            boxCollider.height = data["height"].get<float>();
            boxCollider.body =
                cpBodyNew(1.0f, cpMomentForBox(1.0f, boxCollider.width, boxCollider.height));
            boxCollider.shape =
                cpBoxShapeNew(boxCollider.body, boxCollider.width, boxCollider.height, 0.0f);
            cpShapeSetCollisionType(boxCollider.shape, 1);  // TODO : mutliple collision type
            registry.addComponent<Components::BoxCollider>(entity, std::move(boxCollider));
        });
    componentFactory.registerComponent(
        "Area2D",
        [this](Entity entity, const nlohmann::json& data, Registry& registry)
        {
            struct Components::Area2D area2d;

            area2d.width = data["width"].get<int>();
            area2d.height = data["height"].get<int>();
            registry.addComponent<Components::Area2D>(entity, std::move(area2d));
        });
}
