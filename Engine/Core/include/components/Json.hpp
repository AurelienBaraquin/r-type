#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace Components {
struct Json {
    nlohmann::json data;
};
}  // namespace Components