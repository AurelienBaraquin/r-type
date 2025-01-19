#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace Components {
struct Json {
    std::string data;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(data);
    }
};
}  // namespace Components