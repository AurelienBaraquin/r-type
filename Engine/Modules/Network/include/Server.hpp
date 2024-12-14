#include <asio.hpp>
#include <iostream>
#include <vector>

using asio::ip::udp;

class Server {
public:
    Server(asio::io_context& io_context, unsigned short port)
        : socket_(io_context, udp::endpoint(udp::v4(), port))
    {
        start_receive();
    }

    void send_to_all(const std::vector<uint8_t>& data) {
        for (auto& client : clients_) {
            socket_.async_send_to(asio::buffer(data), client,
                [this](std::error_code, std::size_t) {
                }
            );
        }
    }

private:
    void start_receive() {
        socket_.async_receive_from(
            asio::buffer(recv_buffer_), remote_endpoint_,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    handle_receive(bytes_recvd);
                } 
                start_receive();
            }
        );
    }

    void handle_receive(std::size_t length) {
        std::cout << "Received: " << length << " bytes\n";
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<uint8_t, 1024> recv_buffer_;
    std::vector<udp::endpoint> clients_;
};
