#include "RType.hpp"
#include "Graphic.hpp"
#include "Import.hpp"

IMPORT_ASSETS(assets, "../../../Games/RType/assets/r-typesheet1.gif");

int main()
{
    Engine engine;
    auto& graphic = engine.addModule<Graphic>("R-Type", 800, 600);

    graphic.loadTexture(0, gassetsData, gassetsSize);

    engine.run();

    return 0;
}
