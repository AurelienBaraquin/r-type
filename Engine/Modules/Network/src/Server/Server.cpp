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
        auto *pos = registry.getComponent<Components::Position>(entity);
        entityData data = {
            .entity = entity,
            .x = pos->x,
            .y = pos->y,
            .z = pos->z,
        };
        entities.push_back(data);
    }
    SnapShot snap = {
        .id = id++,
        .entities = entities,
    };
    std::string bin = serializeToString(snap);
    std::cout << bin << std::endl;
    SnapShot snap2 = deserializeFromString<SnapShot>(bin);
    std::cout << snap2.id << std::endl;
    for (auto entity : snap2.entities) {
        std::cout << entity.x << std::endl;
    }
    return generateSnapshot(entities);
}

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    static auto lastSnapShotTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - lastSnapShotTime;

    if (elapsedTime.count() >= 1.0f) {
        server.sendAll(this->snapShot(registry));
        lastSnapShotTime = currentTime;
    }
}
#endif
