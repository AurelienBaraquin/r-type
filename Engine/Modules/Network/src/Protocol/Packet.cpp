#include "Packet.hpp"

Packet::Packet()
{
    header.magic = MAGIC;
    header.version = PROTOCOL_VERSION;
    header.payloadLength = 0;
    header.checksum = 0;
}

std::vector<uint8_t> Packet::serialize() const
{
    uint32_t chksum = computeChecksum();

    std::vector<uint8_t> buffer(sizeof(PacketHeader) + payload.size());
    PacketHeader tmp = header;
    tmp.checksum = chksum;

    std::memcpy(buffer.data(), &tmp, sizeof(PacketHeader));

    if (!payload.empty()) {
        std::memcpy(buffer.data() + sizeof(PacketHeader), payload.data(), payload.size());
    }
    return buffer;
}

bool Packet::deserialize(const uint8_t* data, size_t size)
{
    if (size < sizeof(PacketHeader)) {
        return false;
    }

    PacketHeader hdr;
    std::memcpy(&hdr, data, sizeof(PacketHeader));

    if (hdr.magic != MAGIC) return false;
    if (hdr.version != PROTOCOL_VERSION) return false;
    if (sizeof(PacketHeader) + hdr.payloadLength > size) return false;

    payload.resize(hdr.payloadLength);
    if (hdr.payloadLength > 0) {
        std::memcpy(payload.data(), data + sizeof(PacketHeader), hdr.payloadLength);
    }

    header = hdr;
    uint32_t receivedChecksum = hdr.checksum;
    header.checksum = 0;
    uint32_t computed = computeChecksum();

    if (computed != receivedChecksum) {
        return false;
    }

    return true;
}

static uint32_t simpleChecksum(const uint8_t* data, size_t length)
{
    uint32_t sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += data[i];
    }
    return sum;
}

uint32_t Packet::computeChecksum() const
{
    PacketHeader hdr = header;
    hdr.checksum = 0;

    std::vector<uint8_t> temp(sizeof(PacketHeader) + payload.size());
    std::memcpy(temp.data(), &hdr, sizeof(PacketHeader));
    if (!payload.empty()) {
        std::memcpy(temp.data() + sizeof(PacketHeader), payload.data(), payload.size());
    }

    return simpleChecksum(temp.data(), temp.size());
}

void Packet::setMessageType(MessageType type)
{
    header.msgType = static_cast<uint8_t>(type);
}

void Packet::setPayload(const std::vector<uint8_t>& data)
{
    payload = data;
    header.payloadLength = static_cast<uint16_t>(data.size());
}

MessageType Packet::getMessageType() const
{
    return static_cast<MessageType>(header.msgType);
}
