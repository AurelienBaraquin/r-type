#include "SuperMario.hpp"

int main()
{
    Engine engine;
    engine.addModule<Graphic>("R-Type", 384 * 2, 256 * 2);
    engine.addModule<Inputs>();
    engine.addModule<Physics>();
    engine.addModule<Audio>();

    // engine.loadScene("Games/RType/config/scene.json");

    engine.run();

    return 0;
}
