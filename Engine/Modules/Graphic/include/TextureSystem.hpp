#pragma once

#if defined(_WIN32)
extern "C" {
#endif
#include <raylib.h>
#if defined(_WIN32)
}
#endif

#include <Loader.hpp>
#include <string>
#include <unordered_map>

class TextureSystem : public ILoader
{
   public:
    void loadTexture(int textureID, const std::string& path);
    void remove(int textureID);
    Texture2D get(int textureID) const;

    void load(const nlohmann::json& data) override;
    std::string getPart() override
    {
        return "textures";
    }

    int getSize()
    {
        return textures.size();
    }

   private:
    std::unordered_map<int, Texture2D> textures;
};
