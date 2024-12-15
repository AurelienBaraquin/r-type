#include "Protocol.hpp"

#include <cstring>  // for memcpy

// Placeholder checksum function. In reality, implement a proper CRC32.
static uint32_t simpleChecksum(const uint8_t* data, size_t length)
{
    // Very naive checksum example: sum all bytes
    uint32_t sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += data[i];
    }
    return sum;
}

std::vector<uint8_t> Packet::serialize() const
{
    // Compute checksum first
    uint32_t chksum = computeChecksum();

    std::vector<uint8_t> buffer(sizeof(PacketHeader) + payload.size());
    PacketHeader tmp = header;
    tmp.checksum = chksum;

    // Copy header
    std::memcpy(buffer.data(), &tmp, sizeof(PacketHeader));

    // Copy payload
    if (!payload.empty()) {
        std::memcpy(buffer.data() + sizeof(PacketHeader), payload.data(), payload.size());
    }
    return buffer;
}

bool Packet::deserialize(const uint8_t* data, size_t size)
{
    if (size < sizeof(PacketHeader)) {
        return false;  // too small
    }

    PacketHeader hdr;
    std::memcpy(&hdr, data, sizeof(PacketHeader));

    // Basic checks
    if (hdr.magic != MAGIC) return false;
    if (hdr.version != PROTOCOL_VERSION) return false;
    if (sizeof(PacketHeader) + hdr.payloadLength > size) return false;

    // Extract payload
    payload.resize(hdr.payloadLength);
    if (hdr.payloadLength > 0) {
        std::memcpy(payload.data(), data + sizeof(PacketHeader), hdr.payloadLength);
    }

    // Verify checksum
    header = hdr;  // store temporarily
    uint32_t receivedChecksum = hdr.checksum;
    header.checksum = 0;  // clear for computation
    uint32_t computed = computeChecksum();

    if (computed != receivedChecksum) {
        return false;
    }

    return true;
}

uint32_t Packet::computeChecksum() const
{
    // Compute checksum over header (with checksum=0) and payload
    PacketHeader hdr = header;
    hdr.checksum = 0;

    std::vector<uint8_t> temp(sizeof(PacketHeader) + payload.size());
    std::memcpy(temp.data(), &hdr, sizeof(PacketHeader));
    if (!payload.empty()) {
        std::memcpy(temp.data() + sizeof(PacketHeader), payload.data(), payload.size());
    }

    return simpleChecksum(temp.data(), temp.size());
}
