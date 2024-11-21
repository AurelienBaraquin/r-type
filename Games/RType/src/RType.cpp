#include "RType.hpp"

#include "Inputs.hpp"
#include "Physics.hpp"

int main()
{
    Engine engine;
    auto& graphic = engine.addModule<Graphic>("R-Type", 800, 600);
    auto& inputs = engine.addModule<Inputs>();
    auto& physics = engine.addModule<Physics>();

    engine.loadScene("Games/RType/script/scene.json");

    engine.run();

    return 0;
}
