#pragma once

#include <asio.hpp>
#include <functional>
#include <thread>

#include "Protocol.hpp"

class UdpServer
{
   public:
    UdpServer(asio::io_context& ioContext, unsigned short port);
    void start();

   private:
    void doReceive();
    void handlePacket(const uint8_t* data, size_t length, const asio::ip::udp::endpoint& sender);

    asio::io_context& io_;
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint remoteEndpoint_;
    std::array<uint8_t, 2048> recvBuffer_;  // Increase size as needed
};
