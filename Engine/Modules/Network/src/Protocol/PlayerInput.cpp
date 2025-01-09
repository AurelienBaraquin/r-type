#include "Network.hpp"

Packet generatePlayerInput(int id, std::vector<std::string> dataStr)
{
    Packet p;
    p.setMessageType(MessageType::PLAYER_INPUT);

    PlayerInput pi = {
        .playerID = id,
        .actions = dataStr,
    };

    size_t payloadSize = sizeof(pi.playerID) + sizeof(size_t) +
                         std::accumulate(pi.actions.begin(), pi.actions.end(), (size_t)0,
                                         [](size_t sum, const std::string& s) {
                                             return sum + sizeof(size_t) + s.size();
                                         });

    std::vector<uint8_t> payload(payloadSize);

    uint8_t* ptr = payload.data();
    std::memcpy(ptr, &pi.playerID, sizeof(pi.playerID));
    ptr += sizeof(pi.playerID);

    size_t actionsSize = pi.actions.size();
    std::memcpy(ptr, &actionsSize, sizeof(actionsSize));
    ptr += sizeof(actionsSize);

    for (const auto& action : pi.actions) {
        size_t actionSize = action.size();
        std::memcpy(ptr, &actionSize, sizeof(actionSize));
        ptr += sizeof(actionSize);
        std::memcpy(ptr, action.data(), actionSize);
        ptr += actionSize;
    }

    p.setPayload(payload);
    return p;
}

PlayerInput loadInputFromPacket(const Packet& p)
{
    const uint8_t* ptr = p.payload.data();
    const uint8_t* end = ptr + p.payload.size();
    PlayerInput pi = {0};

    if (ptr + sizeof(pi.playerID) > end) {
        std::cerr << "Server: Payload too short for playerID\n";
        return pi;
    }
    std::memcpy(&pi.playerID, ptr, sizeof(pi.playerID));
    ptr += sizeof(pi.playerID);

    size_t actionsCount;
    if (ptr + sizeof(actionsCount) > end) {
        std::cerr << "Server: Payload too short for actionsCount\n";
        return pi;
    }
    std::memcpy(&actionsCount, ptr, sizeof(actionsCount));
    ptr += sizeof(actionsCount);

    pi.actions.reserve(actionsCount);
    for (size_t i = 0; i < actionsCount; ++i) {
        size_t actionSize;
        if (ptr + sizeof(actionSize) > end) {
            std::cerr << "Server: Payload too short for actionSize\n";
            return pi;
        }
        std::memcpy(&actionSize, ptr, sizeof(actionSize));
        ptr += sizeof(actionSize);

        if (ptr + actionSize > end) {
            std::cerr << "Server: Payload too short for action data\n";
            return pi;
        }
        std::string action(reinterpret_cast<const char*>(ptr), actionSize);
        ptr += actionSize;
        pi.actions.push_back(std::move(action));
    }
    return pi;
}
