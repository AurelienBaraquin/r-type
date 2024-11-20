#include "RType.hpp"

IMPORT_ASSETS(assets, "../../../Games/RType/assets/r-typesheet32.gif");

int main()
{
    Engine engine;
    auto& graphic = engine.addModule<Graphic>("R-Type", 800, 600);

    graphic.manageTextures().loadTexture(0, gassetsData, gassetsSize);

    engine.manageScene().loadScene("Games/RType/script/scene.json");

    engine.run();

    return 0;
}
