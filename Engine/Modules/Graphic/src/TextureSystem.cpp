#include "TextureSystem.hpp"
#include <stdexcept>
#include "Log.hpp"

void TextureSystem::loadTexture(int textureID, const std::string& path) {
    Texture2D texture = LoadTexture(path.c_str());
    if (texture.id == 0) {
        Logger::getInstance().error("Failed to load texture: " + path);
        return;
    }
    textures[textureID] = texture;
    this->get(textureID);
}

void TextureSystem::remove(int textureID) {
    // auto it = textures.find(textureID);
    // if (it != textures.end()) {
    //     UnloadTexture(it->second);
    //     textures.erase(it);
    // }
}

Texture2D TextureSystem::get(int textureID) const {
    auto it = textures.find(textureID);
    if (it != textures.end()) {
        return it->second;
    }
    return {0};
}

void TextureSystem::load(const nlohmann::json& data) {
    for (const auto& textureData : data) {
        int textureID = textureData["textureID"].get<int>();
        std::string path = textureData["path"].get<std::string>();

        loadTexture(textureID, path);
    }
    std::cout << "texture size is now: " << textures.size() << std::endl;
}
