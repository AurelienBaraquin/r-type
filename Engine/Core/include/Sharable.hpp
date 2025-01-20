#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

class Sharable
{
   public:
    using SharedData = std::variant<int, float, bool, std::string, std::vector<std::string>>;

    void setSharedVariable(const std::string& name, const SharedData& value)
    {
        sharedVariables[name] = value;
    }

    std::optional<SharedData> getSharedVariable(const std::string& name) const
    {
        if (auto it = sharedVariables.find(name); it != sharedVariables.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    static Sharable& getInstance()
    {
        static Sharable instance;
        return instance;
    }

   private:
    std::unordered_map<std::string, SharedData> sharedVariables;
};
