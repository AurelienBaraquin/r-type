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
    {
        std::ifstream is("registry.dat", std::ios::binary);
        if (!is) {
            std::cerr << "Failed to open file for loading.\n";
            return;
        }
        cereal::BinaryInputArchive archive(is);
        registry.clear();
        archive(registry);
        // std::cout << "Registry loaded successfully.\n";
    }
    std::vector<std::string> dataStr = getDatas();

    auto p = generatePlayerInput(this->id, dataStr);

    client.sendPacket(p);
    Packet pa = getSnapShot();
    if (pa.getMessageType() == MessageType::SNAPSHOT) {
        std::cout << "Client: Received SNAPSHOT from server.\n";
        std::string sn = pa.getPayload<SnapShot>().entities;
        std::cout << sn << std::endl;
        std::istringstream is(sn);
        cereal::BinaryInputArchive archive(is);
        registry.load(archive);
        // std::cout << "Client: Received SNAPSHOT from server.\n";
        // updateEntity(registry, p.getPayload<SnapShot>().data);
    }
}
#endif
