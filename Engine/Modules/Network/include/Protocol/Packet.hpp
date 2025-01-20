#pragma once
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "Registry.hpp"
#include "MessageType.hpp"

static constexpr uint16_t MAGIC = 0xABCD;
static constexpr uint8_t PROTOCOL_VERSION = 0x01;

struct PacketHeader {
    uint16_t magic;          // 0xABCD
    uint8_t version;         // current protocol version
    uint8_t msgType;         // one of MessageType
    uint16_t payloadLength;  // length of payload
    uint32_t checksum;       // CRC32 or similar

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(magic, version, msgType, payloadLength, checksum);
    }
};

// Base class for all payload types
class IPayload
{
   public:
    virtual ~IPayload() = default;
    virtual std::vector<uint8_t> serialize() const = 0;
    virtual void deserialize(const std::vector<uint8_t>& data) = 0;
};

class Packet
{
   public:
    Packet()
    {
        header.magic = MAGIC;
        header.version = PROTOCOL_VERSION;
    }

    ~Packet() = default;

    template <typename T>
    void setPayload(const T& data)
    {
        std::ostringstream os;
        {
            cereal::BinaryOutputArchive archive(os);
            archive(data);
        }
        std::string str = os.str();
        payload = std::vector<uint8_t>(str.begin(), str.end());
        header.payloadLength = payload.size();
        header.checksum = computeChecksum();
    }

    template <typename T>
    T getPayload() const
    {
        T result;
        if (!payload.empty()) {
            std::string str(payload.begin(), payload.end());
            std::istringstream is(str);
            cereal::BinaryInputArchive archive(is);
            archive(result);
        }
        return result;
    }

    std::vector<uint8_t> serialize() const
    {
        std::ostringstream os;
        {
            cereal::BinaryOutputArchive archive(os);
            archive(header);
            archive(payload);
        }
        std::string str = os.str();
        return std::vector<uint8_t>(str.begin(), str.end());
    }

    bool deserialize(const uint8_t* data, size_t size)
    {
        try {
            std::string str(reinterpret_cast<const char*>(data), size);
            std::istringstream is(str);
            cereal::BinaryInputArchive archive(is);
            archive(header);
            archive(payload);
            return header.magic == MAGIC;
        } catch (...) {
            return false;
        }
    }

    uint32_t computeChecksum() const
    {
        // Implement your checksum calculation here
        // Example using simple sum
        uint32_t sum = 0;
        for (const auto& byte : payload) {
            sum += byte;
        }
        return sum;
    }

    void setMessageType(MessageType type)
    {
        header.msgType = static_cast<uint8_t>(type);
    }

    MessageType getMessageType() const
    {
        return static_cast<MessageType>(header.msgType);
    }

    PacketHeader header = {};
    std::vector<uint8_t> payload;
};

inline Packet generatePlayerInput(int id, std::vector<std::string> dataStr)
{
    Packet packet;
    PlayerInput pi = {id, dataStr};

    packet.setMessageType(MessageType::PLAYER_INPUT);
    packet.setPayload(pi);
    return packet;
}

inline PlayerInput loadInputFromPacket(const Packet& p)
{
    if (p.getMessageType() != MessageType::PLAYER_INPUT) {
        throw std::runtime_error("Invalid packet type");
    }
    return p.getPayload<PlayerInput>();
}

inline Packet generateSnapshot(const Registry registry)
{
    static size_t id = 0;
 
    Packet packet;
    SnapShot snap = {id++, registry};

    packet.setMessageType(MessageType::SNAPSHOT);
    packet.setPayload(snap);
    return packet;
}

// inline Registry loadSnapshotFromPacket(const Packet& p)
// {
//     if (p.getMessageType() != MessageType::SNAPSHOT) {
//         throw std::runtime_error("Invalid packet type");
//     }
//     std::string registryData = p.getPayload<SnapShot>();
//     std::istringstream is(registryData);
//     cereal::BinaryInputArchive archive(is);
    
//     return registry;
// }