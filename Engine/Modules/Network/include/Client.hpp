#include <asio.hpp>
#include <iostream>

using asio::ip::udp;

class Client {
public:
    Client(asio::io_context& io_context, const std::string& server_ip, unsigned short server_port)
        : socket_(io_context)
    {
        udp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(udp::v4(), server_ip, std::to_string(server_port));
        server_endpoint_ = *endpoints.begin();
        
        socket_.open(udp::v4());
        send_handshake();
        start_receive();
    }

    void send_input(const std::vector<uint8_t>& input_data) {
        socket_.async_send_to(
            asio::buffer(input_data), server_endpoint_,
            [this](std::error_code, std::size_t) {
            }
        );
    }

private:
    void send_handshake() {
        std::vector<uint8_t> handshake_packet = create_handshake_packet();
        socket_.async_send_to(
            asio::buffer(handshake_packet), server_endpoint_,
            [this](std::error_code, std::size_t) {
            }
        );
    }

    void start_receive() {
        socket_.async_receive_from(
            asio::buffer(recv_buffer_), sender_endpoint_,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    handle_state_update(bytes_recvd);
                }
                start_receive();
            }
        );
    }

    void handle_state_update(std::size_t length) {
        std::cout << "Received state update: " << length << " bytes\n";
    }

    std::vector<uint8_t> create_handshake_packet() {
        return {0x00, 0x01};
    }

    udp::socket socket_;
    udp::endpoint server_endpoint_;
    udp::endpoint sender_endpoint_;
    std::array<uint8_t, 1024> recv_buffer_;
};
