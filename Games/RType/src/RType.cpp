#include "RType.hpp"
#include "Graphic.hpp"

#include <iostream>

int main()
{
    Engine().addSystem<Graphic>("RType", 800, 600)
            .run();
}
