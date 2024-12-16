#pragma once

#include <array>
#include <cstdint>
#include <vector>

static constexpr uint16_t MAGIC = 0xABCD;
static constexpr uint8_t PROTOCOL_VERSION = 0x01;

enum class MessageType : uint8_t {
    PLAYER_UPDATE = 0x01,
    WORLD_EVENT = 0x02,
    SERVER_SNAPSHOT = 0x03,
    PLAYER_INPUT = 0x04,
};

#pragma pack(push, 1)
struct PacketHeader {
    uint16_t magic;          // 0xABCD
    uint8_t version;         // current protocol version
    uint8_t msgType;         // one of MessageType
    uint32_t sequence;       // sequence number
    uint16_t payloadLength;  // length of payload
    uint32_t checksum;       // CRC32 or similar
};
#pragma pack(pop)

class Packet
{
   public:
    PacketHeader header = {};
    std::vector<uint8_t> payload;

    Packet()
    {
        header.magic = MAGIC;
        header.version = PROTOCOL_VERSION;
        header.payloadLength = 0;
        header.checksum = 0;
    }

    std::vector<uint8_t> serialize() const;

    bool deserialize(const uint8_t* data, size_t size);

    uint32_t computeChecksum() const;

    void setMessageType(MessageType type)
    {
        header.msgType = static_cast<uint8_t>(type);
    }

    void setSequence(uint32_t seq)
    {
        header.sequence = seq;
    }

    void setPayload(const std::vector<uint8_t>& data)
    {
        payload = data;
        header.payloadLength = static_cast<uint16_t>(data.size());
    }

    MessageType getMessageType() const
    {
        return static_cast<MessageType>(header.msgType);
    }
};
