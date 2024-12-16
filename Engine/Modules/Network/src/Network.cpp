#include "Network.hpp"

#ifdef CLIENT
Network::Network()
    : ioContext(),
      client(ioContext, asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345))
{
    try {
        Packet p;
        p.setMessageType(MessageType::PLAYER_UPDATE);
        p.setSequence(1);

        struct PlayerUpdate {
            uint32_t playerID;
            float pos[3];
            float vel[3];
        } pu;
        pu.playerID = 42;
        pu.pos[0] = 1.0f;
        pu.pos[1] = 2.0f;
        pu.pos[2] = 3.0f;
        pu.vel[0] = 0.0f;
        pu.vel[1] = 0.0f;
        pu.vel[2] = 0.0f;

        std::vector<uint8_t> payload(sizeof(PlayerUpdate));
        std::memcpy(payload.data(), &pu, sizeof(PlayerUpdate));
        p.setPayload(payload);

        client.sendPacket(p);
        std::cout << "Client: Packet sent.\n";
    } catch (std::exception &e) {
        std::cerr << "Client exception: " << e.what() << "\n";
    }
}

void Network::update(float deltaTime, Registry &registry, ScriptSystem &scriptSystem)
{
    // auto* input = registry.getComponent<Components::Input>(entity);
    // if (!input)
    //     throw std::runtime_error("Input component not found");
    // std::cout << "Input " <<  input.inputConfigID << std::endl;
    // Packet p;
    // p.setMessageType(MessageType::PLAYER_INPUT);

    // p.setSequence(1);

    // struct PlayerInput {
    //     uint32_t playerID;
    // } pi;

    // pi.PlayerID = 42;

    // std::vector<uint8_t> payload(sizeof(PlayerInput));
    // std::memcpy(payload.data(), &pi, sizeof(PlayerInput));
    // p.setPayload(payload);
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
