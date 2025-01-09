#include <asio.hpp>
#include <iostream>

#include "Network.hpp"
#include "UdpClient.hpp"
#include "Sharable.hpp"

#ifdef CLIENT
Network::Network()
    : ioContext(),
      client(ioContext, asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345))
{
    client.startReceiving();

    std::thread ioThread = std::thread([this]() {
        ioContext.run();
    });
    ioThread.detach();
}

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    auto data = Sharable::getInstance().getSharedVariable("InputStates");
    Sharable::getInstance().setSharedVariable("InputStates", std::vector<std::string>{});
    std::vector<std::string> dataStr;

    if (data.has_value()) {
        if (auto inputVec = std::get_if<std::vector<std::string>>(&(*data))) {
            dataStr = *inputVec;
        }
    }

    Packet p;
    p.setMessageType(MessageType::PLAYER_INPUT);
    p.setSequence(1);

    struct PlayerInput {
        uint32_t playerID;
        std::vector<std::string> actions;
    } pi;
    pi.playerID = 42;
    pi.actions = dataStr;

    size_t payloadSize =
        sizeof(pi.playerID) + sizeof(size_t) +
        std::accumulate(pi.actions.begin(), pi.actions.end(), (size_t)0,
                        [](size_t sum, const std::string& s) { return sum + sizeof(size_t) + s.size(); });

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

    client.sendPacket(p);
}
#endif
