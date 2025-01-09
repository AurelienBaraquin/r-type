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
                                         [](size_t sum, const std::string &s) {
                                             return sum + sizeof(size_t) + s.size();
                                         });

    std::vector<uint8_t> payload(payloadSize);

    uint8_t *ptr = payload.data();
    std::memcpy(ptr, &pi.playerID, sizeof(pi.playerID));
    ptr += sizeof(pi.playerID);

    size_t actionsSize = pi.actions.size();
    std::memcpy(ptr, &actionsSize, sizeof(actionsSize));
    ptr += sizeof(actionsSize);

    for (const auto &action : pi.actions) {
        size_t actionSize = action.size();
        std::memcpy(ptr, &actionSize, sizeof(actionSize));
        ptr += sizeof(actionSize);
        std::memcpy(ptr, action.data(), actionSize);
        ptr += actionSize;
    }

    p.setPayload(payload);
    return p;
}
