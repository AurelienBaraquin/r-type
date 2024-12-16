#pragma once

#include <raylib.h>
#include <unordered_map>
#include <string>
#include <Loader.hpp>

class TextureSystem : public ILoader {
public:
    void loadTexture(int textureID, const std::string& path);
    void remove(int textureID);
    Texture2D get(int textureID) const;

    void load(const nlohmann::json& data) override;
    std::string getPart() override { return "textures"; }

private:
    std::unordered_map<int, Texture2D> textures;
};
