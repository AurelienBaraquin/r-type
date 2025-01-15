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

    
}
SnapShot loadSnapShot(const Packet& packet)
{
    // std::serialize(packet)
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