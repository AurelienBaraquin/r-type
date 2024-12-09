#include <asio.hpp>

#ifdef SERVER
    void receiveData(asio::ip::udp::socket& socket, char* data, asio::ip::udp::endpoint& sender_endpoint, size_t& length)
    {
        length = socket.receive_from(asio::buffer(data, 1024), sender_endpoint);
    }

    std::string processData(const char* data, size_t length)
    {
        return std::string(data, length);
    }

    void sendResponse(asio::ip::udp::socket& socket, const std::string& response, const asio::ip::udp::endpoint& sender_endpoint)
    {
        socket.send_to(asio::buffer(response), sender_endpoint);
    }

    void Network::update(float deltaTime, Registry& registry, ScriptSystem& scriptSystem)
    {
        asio::io_context io_context;
        asio::ip::udp::socket socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 12345));

        char data[1024];
        asio::ip::udp::endpoint sender_endpoint;
        size_t length;

        receiveData(socket, data, sender_endpoint, length);

        std::string message = processData(data, length);

        std::string response = "Message received";
        sendResponse(socket, response, sender_endpoint);
    }
#endif
