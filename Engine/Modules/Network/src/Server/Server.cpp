#include <asio.hpp>
#include <iostream>

#include "Network.hpp"
#include "Sharable.hpp"
#include "UdpServer.hpp"
#include "Transform.hpp"


#ifdef SERVER
Network::Network() : ioContext(), server(ioContext, 12345)
{
    try {
        server.start();

        std::thread t([this]() { this->ioContext.run(); });

        std::cout << "Server running on port 12345...\n";

        t.detach();

    } catch (std::exception &e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
    }
}

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    RegistryLock lock(registry);

    std::vector<Entity> entitiesToDraw;

        for (auto entity : registry.view<Components::Position,
                                        Components::Scale, Components::Rotation>()) {
            entitiesToDraw.push_back(entity);
        }

    
    for (auto entity: entitiesToDraw) {
        auto *pos = registry.getComponent<Components::Position>(entity);

        std::cout << "Server: Drawing x;" << pos->x << " y;" << pos->y << " z:" << pos->z << std::endl;
    }
}
#endif
