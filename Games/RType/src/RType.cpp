#include "RType.hpp"
#include "Graphic.hpp"
#include "Import.hpp"

#include "Transform.hpp"
#include "Sprite.hpp"

#include <iostream>

IMPORT_ASSETS(assets, "../../../Games/RType/assets/r-typesheet1.gif");

int main()
{
    Engine engine;
    auto& graphic = engine.addModule<Graphic>("R-Type", 800, 600);

    graphic.loadTexture(0, gassetsData, gassetsSize);

    engine.addEntity()
        .addComponent<Components::Position>(400, 300, 0)
        .addComponent<Components::Scale>(1, 1)
        .addComponent<Components::Rotation>(0.0f)
        .addComponent<Components::Sprite>(0, 32, 32, 16, 16)
        .build();

    engine.run();

    return 0;
}
