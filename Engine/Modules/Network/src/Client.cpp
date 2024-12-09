#include "Network.hpp"
#include <asio.hpp>

#ifdef CLIENT
    void sendMessage(asio::ip::udp::socket& socket, const asio::ip::udp::endpoint& receiver_endpoint, const std::string& message)
    {
        socket.send_to(asio::buffer(message), receiver_endpoint);
    }

    std::string receiveMessage(asio::ip::udp::socket& socket, asio::ip::udp::endpoint& sender_endpoint)
    {
        char data[1024];
        size_t length = socket.receive_from(asio::buffer(data), sender_endpoint);
        return std::string(data, length);
    }

    asio::ip::udp::endpoint resolveEndpoint(asio::io_context& io_context, const std::string& host, const std::string& port)
    {
        asio::ip::udp::resolver resolver(io_context);
        return *resolver.resolve(asio::ip::udp::v4(), host, port).begin();
    }

    void Network::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
    {
        asio::io_context io_context;
        asio::ip::udp::endpoint receiver_endpoint = resolveEndpoint(io_context, "localhost", "12345");

        asio::ip::udp::socket socket(io_context);
        socket.open(asio::ip::udp::v4());

        std::string message = "Hello from client";
        sendMessage(socket, receiver_endpoint, message);

        asio::ip::udp::endpoint sender_endpoint;
        std::string response = receiveMessage(socket, sender_endpoint);
    }
#endif
