#pragma once

#include <array>
#include <asio.hpp>
#include <functional>
#include <thread>

#include "Protocol.hpp"

class UdpClient
{
   public:
    UdpClient(asio::io_context& ioContext, const asio::ip::udp::endpoint& serverEndpoint);
    void sendPacket(const Packet& packet);

    void startReceiving();

   private:
    void doReceive();
    void handleReceive(const std::error_code& ec, std::size_t bytes_received);

    asio::io_context& io_;
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint serverEndpoint_;
    asio::ip::udp::endpoint remoteEndpoint_;
    std::array<uint8_t, 2048> recvBuffer_;
};
