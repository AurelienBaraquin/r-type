#include "RType.hpp"
#include "Inputs.hpp"
#include "Physics.hpp"

IMPORT_ASSETS(assets, "../../../Games/RType/assets/r-typesheet32.gif");

int main()
{
    Engine engine;
    auto& graphic = engine.addModule<Graphic>("R-Type", 800, 600);
    auto& inputs = engine.addModule<Inputs>();
    auto& physics = engine.addModule<Physics>(engine.getScriptSystem());

    graphic.manageTextures().loadTexture(0, gassetsData, gassetsSize);

    engine.manageScene().load("Games/RType/script/scene.json");

    engine.run();

    return 0;
}
