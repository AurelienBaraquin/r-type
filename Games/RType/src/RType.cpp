#include "RType.hpp"

int main()
{
    Engine engine;
#ifdef BUILD_GRAPHIC
    engine.addModule<Graphic>("R-Type", 800, 600);
#endif
#ifdef BUILD_AUDIO
    engine.addModule<Audio>();
#endif
    engine.addModule<Inputs>();
    engine.addModule<Physics>();
    engine.addModule<Network>();

    engine.loadScene("Games/RType/config/scene.json");

    engine.run();

    return 0;
}
