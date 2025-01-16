#include "Network.hpp"

std::vector<entityData>& updateSnapshot(const std::vector<entityData>& newSnapshot, bool set)
{
    static std::vector<entityData> snap;

    if (set)
    {
        snap = newSnapshot;
    }
    return snap;
}

const std::vector<entityData>& getSnapShot()
{
    static const std::vector<entityData> emptySnapshot;
    return updateSnapshot(emptySnapshot, false);
}

void setSnapshot(const std::vector<entityData>& newSnapshot)
{
    updateSnapshot(newSnapshot, true);
}