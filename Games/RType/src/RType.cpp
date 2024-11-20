#include "RType.hpp"

IMPORT_ASSETS(assets, "../../../Games/RType/assets/r-typesheet32.gif");

int main()
{
    Engine engine;
    auto& graphic = engine.addModule<Graphic>("R-Type", 800, 600);

    graphic.manageTextures().loadTexture(0, gassetsData, gassetsSize);

    graphic.manageSprites().loadSprite(0, 0, 260, 143, 0, 0);

    graphic.manageAnimations().loadAnimations("Games/RType/script/scene.json");

    engine.manageScene().loadScene("Games/RType/script/scene.json");

    engine.run();

    return 0;
}
