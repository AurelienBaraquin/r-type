#include "UdpClient.hpp"

#include <iostream>

UdpClient::UdpClient(asio::io_context& ioContext, const asio::ip::udp::endpoint& serverEndpoint)
    : io_(ioContext), socket_(ioContext), serverEndpoint_(serverEndpoint)
{
    socket_.open(asio::ip::udp::v4());
}

void UdpClient::sendPacket(const Packet& packet)
{
    auto buffer = packet.serialize();
    socket_.send_to(asio::buffer(buffer), serverEndpoint_);
}
