#pragma once

#include <cereal/archives/binary.hpp>
#include <sstream>
#include <string>

template <typename T>
std::string serializeToString(const T& obj) {
    std::ostringstream oss;
    {
        cereal::BinaryOutputArchive archive(oss);
        archive(obj);
    }
    return oss.str();
}

template <typename T>
T deserializeFromString(const std::string& data) {
    std::istringstream iss(data);
    T obj;
    {
        cereal::BinaryInputArchive archive(iss);
        archive(obj);
    }
    return obj;
}