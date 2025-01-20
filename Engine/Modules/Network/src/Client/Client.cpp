#include <stdlib.h>
#include <time.h>

#include <asio.hpp>
#include <iostream>

#include "Network.hpp"
#include "Sharable.hpp"
#include "UdpClient.hpp"

#ifdef CLIENT
Network::Network()
    : ioContext(),
      client(ioContext, asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345))
{
    client.startReceiving();

    std::thread ioThread = std::thread([this]() { ioContext.run(); });
    ioThread.detach();

    srand(time(NULL));
    this->id = rand() % 100000;
}

std::vector<std::string> getDatas()
{
    auto data = Sharable::getInstance().getSharedVariable("InputStates");
    Sharable::getInstance().setSharedVariable("InputStates", std::vector<std::string>{});
    std::vector<std::string> dataStr;

    if (data.has_value()) {
        if (auto inputVec = std::get_if<std::vector<std::string>>(&(*data))) {
            dataStr = *inputVec;
        }
    }
    return dataStr;
}

void updateC(Registry &registry, Entity entity, entityData data)
{

}

// void Network::updateEntity(Registry &registry, std::vector<entityData> snap)
// {
//     for (auto entity : snap) {
//         if (!registry.hasTag(entity.entity, "server")) {
//             Entity newEnt = registry.createEntity(entity.tag);
//             registry.addTag(newEnt, "server");
//             ServerToClient[entity.entity] = entity;
//         }
//         updateC(registry, ServerToClient[entity.entity], entity);
//     }
// }

// void removeWithoutTag(Registry &registry, Tag tag)
// {
//     for (auto entity : registry.view<Components::Position, Components::Scale, Components::Rotation>()) {
//         if (!registry.hasTag(entity, tag)) {
//             registry.destroyEntity(entity);
//         }
//     }
// }

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    std::ifstream file("registry.txt");
    cereal::BinaryInputArchive archive(file);
    registry.clear();
    archive(registry);

    std::vector<std::string> dataStr = getDatas();

    auto p = generatePlayerInput(this->id, dataStr);

    client.sendPacket(p);
    // removeWithoutTag(registry, "server");
    std::vector<entityData> snap = getSnapShot();
    // if (snap.size() > 0) {
        // setSnapshot(std::vector<entityData>{});
        // udpateEntity(registry, snap);
    // }
    // auto data = Sharable::getInstance().getSharedVariable("Snapshot");
    // Sharable::getInstance().setSharedVariable("Snapshot", std::vector<entityData>{});
    // if (data.has_value()) {
    // if (auto snap = std::get_if<std::vector<entityData>>(&(*data))) {
    // for (auto entity : *snap) {
    // std::cout << "Entity: " << entity.entity << " at (" << entity.x << ", " << entity.y << ", "
    // << entity.z << ")\n";
    // }
    // }
    // }
}
#endif
