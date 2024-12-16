#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <variant>
#include <vector>
#include <optional>

class Sharable {
public:
    using SharedData = std::variant<int, float, bool, std::string, std::vector<std::string>>;

    virtual ~Sharable() = default;

    void registerSharedVariable(const std::string& name, std::function<SharedData()> getter) {
        sharedVariables[name] = getter;
    }

    std::optional<SharedData> getSharedVariable(const std::string& name) const {
        if (sharedVariables.find(name) != sharedVariables.end()) {
            return sharedVariables.at(name)();
        }
        return std::nullopt;
    }

    const std::unordered_map<std::string, std::function<SharedData()>>& getAllSharedVariables() const {
        return sharedVariables;
    }

    static Sharable& getInstance() {
        static Sharable instance;
        return instance;
    }

private:
    std::unordered_map<std::string, std::function<SharedData()>> sharedVariables;
};
