#include "Network.hpp"

Packet generateSnapShot(const std::vector<entityData>& entities)
{
    Packet p;
    p.setMessageType(MessageType::SNAPSHOT);
    static size_t id = 0;

    SnapShot snap = {
        .id = id++,
        .entities = entities,
    };

    size_t payloadSize = sizeof(snap.id) + sizeof(size_t) +
                         std::accumulate(snap.entities.begin(), snap.entities.end(), (size_t)0,
                                         [](size_t sum, const entityData& e) {
                                             return sum + sizeof(e.entityID) + sizeof(e.pos);
                                         });

    std::vector<uint8_t> payload(payloadSize);

    uint8_t* ptr = payload.data();
    std::memcpy(ptr, &snap.id, sizeof(snap.id));
    ptr += sizeof(snap.id);

    size_t entitiesSize = snap.entities.size();
    std::memcpy(ptr, &entitiesSize, sizeof(entitiesSize));
    ptr += sizeof(entitiesSize);

    for (const auto& entity : snap.entities) {
        std::memcpy(ptr, &entity.entityID, sizeof(entity.entityID));
        ptr += sizeof(entity.entityID);
        std::memcpy(ptr, &entity.pos, sizeof(entity.pos));
        ptr += sizeof(entity.pos);
    }

    p.setPayload(payload);
    return p;
}
SnapShot loadSnapShot(const Packet& packet)
{
    // SnapShot snap;
    // const uint8_t *ptr = payload.data();
    // const uint8_t *end = ptr + payload.size();
    // SnapShot snap = {0};

    // if (ptr + sizeof(snap.id) > end) {
    //     std::cerr << "Server: Payload too short for snap.id\n";
    //     return snap;
    // }
    // std::memcpy(&snap.id, ptr, sizeof(snap.id));

    // if (ptr + sizeof(snap.id) > end) {
    //     std::cerr << "Server: Payload too short for snap.id\n";
    //     return snap;
    // }
    // std::memcpy(&snap.id, ptr, sizeof(snap.id));
    // ptr += sizeof(snap.id);

    // size_t entitiesSize;
    // if (ptr + sizeof(entitiesSize) > end) {
    //     std::cerr << "Server: Payload too short for entitiesSize\n";
    //     return snap;
    // }
    // std::memcpy(&entitiesSize, ptr, sizeof(entitiesSize));
    // ptr += sizeof(entitiesSize);

    // snap.entities.resize(entitiesSize);
    // for (auto& entity : snap.entities) {
    //     if (ptr + sizeof(entity.entityID) > end) {
    //         std::cerr << "Server: Payload too short for entity.entityID\n";
    //         return snap;
    //     }
    //     std::memcpy(&entity.entityID, ptr, sizeof(entity.entityID));
    //     ptr += sizeof(entity.entityID);

    //     if (ptr + sizeof(entity.pos) > end) {
    //         std::cerr << "Server: Payload too short for entity.pos\n";
    //         return snap;
    //     }
    //     std::memcpy(&entity.pos, ptr, sizeof(entity.pos));
    //     ptr += sizeof(entity.pos);
    // }

    // return snap;
}