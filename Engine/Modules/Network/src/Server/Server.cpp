#include <asio.hpp>
#include <chrono>
#include <iostream>

#include "Network.hpp"
#include "Sharable.hpp"
#include "Transform.hpp"
#include "UdpServer.hpp"

#ifdef SERVER
Network::Network() : ioContext(), server(ioContext, 12345)
{
    try {
        server.start();

        std::thread t([this]() { this->ioContext.run(); });

        // std::cout << "Server running on port 12345...\n";

        t.detach();

    } catch (std::exception &e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
    }
}

Packet Network::snapShot(Registry &registry)
{
    RegistryLock lock(registry);
    entityData data;
    std::vector<entityData> entities;
    std::vector<Entity> entitiesToSend;
    static size_t id = 0;

    for (auto entity :
         registry.view<Components::Position, Components::Scale, Components::Rotation>()) {
        entitiesToSend.push_back(entity);
    }

    for (auto entity : entitiesToSend) {
        auto pos = registry.getComponent<Components::Position>(entity);
        auto scale = registry.getComponent<Components::Scale>(entity);
        auto rot = registry.getComponent<Components::Rotation>(entity);
        entityData data = {entity, *pos, *scale, *rot};
        entities.push_back(data);
    }
    return generateSnapshot(entities);
}

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    static auto lastSnapShotTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - lastSnapShotTime;

    if (elapsedTime.count() >= 1.0f) {
        {
            std::ofstream file("registry.txt");
            cereal::BinaryOutputArchive archive(file);
            archive(registry);
        }
        server.sendAll(this->snapShot(registry));
        lastSnapShotTime = currentTime;
    }
}
#endif
