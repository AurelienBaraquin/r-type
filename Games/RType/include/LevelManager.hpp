#include <vector>
#include <string>
#include "json.hpp"

class LevelManager {
    std::vector<std::string> levels;
    int currentLevel;

public:
    LevelManager() : currentLevel(0) {}

    void loadLevel(const std::string &filePath) {
        std::ifstream file(filePath);
        nlohmann::json json;
        file >> json;

        for (auto &level : json["levels"]) {
            levels.push_back(level["scene"]);
        }
    }

    std::string getCurrentLevelScene() {
        return levels[currentLevel];
    }

    void nextLevel() {
        if (currentLevel < levels.size() - 1) {
            currentLevel++;
        }
    }
};
