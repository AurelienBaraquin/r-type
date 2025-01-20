#include "Network.hpp"
#include "Packet.hpp"

Packet& updateSnapshot(const Packet& newSnapshot, bool set)
{
    static Packet snap;

    if (set) {
        snap = newSnapshot;
    }
    return snap;
}

const Packet& getSnapShot()
{
    static const Packet emptySnapshot;
    return updateSnapshot(emptySnapshot, false);
}

void setSnapshot(const Packet& newSnapshot)
{
    updateSnapshot(newSnapshot, true);
}