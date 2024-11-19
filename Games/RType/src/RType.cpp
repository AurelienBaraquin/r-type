#include "RType.hpp"

IMPORT_ASSETS(assets, "../../../Games/RType/assets/r-typesheet32.gif");

int main()
{
    Engine engine;
    auto& graphic = engine.addModule<Graphic>("R-Type", 800, 600);

    graphic.loadTexture(0, gassetsData, gassetsSize);

    graphic.loadAnimation(0, {
                                 {0, 260, 143, 260, 0},
                                 {0, 260, 143, 0, 0},
                                 {0, 260, 143, 260, 143},
                                 {0, 260, 143, 0, 143},
                                 {0, 260, 143, 260, 286},
                                 {0, 260, 143, 0, 286},
                                 {0, 260, 143, 260, 429},
                                 {0, 260, 143, 0, 429},
                             });

    engine.addEntity()
        .addComponent<Components::Position>(0, 0, 0)
        .addComponent<Components::Scale>(1, 1)
        .addComponent<Components::Rotation>(0.0f)
        .addComponent<Components::Sprite>(0, 260, 143, 0, 0)
        .addComponent<Components::Animation>(0, 0, 10.0f, 0.0f, false, true)
        .addComponent<Components::Script>("test.lua")
        .build();

    engine.run();

    return 0;
}
