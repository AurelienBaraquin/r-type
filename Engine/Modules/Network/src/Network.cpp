#include "Network.hpp"

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
    const auto &variables = Sharable::getInstance().getAllSharedVariables();
    std::vector<std::string> dataStr;

    for (const auto &[varName, getter] : variables) {
        auto data = getter();
        dataStr = std::get<std::vector<std::string>>(data);
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
        sizeof(pi.playerID) + sizeof(size_t) + pi.actions.size() * sizeof(std::string);
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

#ifdef SERVER
Network::Network() : ioContext(), server(ioContext, 12345)
{
    try {
        server.start();

        std::thread t([this]() { this->ioContext.run(); });

        std::cout << "Server running on port 12345...\n";

        t.detach();

    } catch (std::exception &e) {
        std::cerr << "Server exception: " << e.what() << "\n";
    }
}

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    std::cout << server.countClients() << std::endl;
}
#endif

void Network::registerComponentFactory(ComponentFactory &componentFactory)
{
    // Register network-related components
}

void Network::registerScriptBindings(ScriptSystem &scriptSystem, Registry &registry)
{
    // Register network-related script bindings
}
