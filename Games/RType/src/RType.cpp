#include "RType.hpp"

int main()
{
    Engine engine;
    engine.addModule<Graphic>("R-Type", 800, 600);
    engine.addModule<Inputs>();
    engine.addModule<Physics>();
    engine.addModule<Audio>();

    engine.loadScene("Games/RType/config/scene.json");

    engine.run();

    return 0;
}
