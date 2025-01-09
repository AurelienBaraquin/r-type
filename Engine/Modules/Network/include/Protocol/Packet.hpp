#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

#include "MessageType.hpp"

static constexpr uint16_t MAGIC = 0xABCD;
static constexpr uint8_t PROTOCOL_VERSION = 0x01;

#pragma pack(push, 1)
struct PacketHeader {
    uint16_t magic;          // 0xABCD
    uint8_t version;         // current protocol version
    uint8_t msgType;         // one of MessageType
    uint16_t payloadLength;  // length of payload
    uint32_t checksum;       // CRC32 or similarPacket
};
#pragma pack(pop)

class Packet
{
   public:
    Packet();
    ~Packet() = default;

    std::vector<uint8_t> serialize() const;
    bool deserialize(const uint8_t* data, size_t size);

    uint32_t computeChecksum() const;

    void setMessageType(MessageType type);
    void setPayload(const std::vector<uint8_t>& data);

    MessageType getMessageType() const;

    PacketHeader header = {};
    std::vector<uint8_t> payload;
};
