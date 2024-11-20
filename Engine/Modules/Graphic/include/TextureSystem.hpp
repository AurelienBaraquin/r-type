#pragma once

#include <unordered_map>

struct Texture
{
    const unsigned char* data;
    std::size_t size;
};

class TextureSystem
{
   public:
    void loadTexture(int textureID, const unsigned char* data, std::size_t size);
    void removeTexture(int textureID);
    const Texture& getTexture(int textureID);

    // begin
    std::unordered_map<int, Texture>::iterator begin()
    {
        return textures.begin();
    }
    std::unordered_map<int, Texture>::const_iterator begin() const
    {
        return textures.begin();
    }
    std::unordered_map<int, Texture>::const_iterator cbegin() const
    {
        return textures.cbegin();
    }
    // end
    std::unordered_map<int, Texture>::iterator end()
    {
        return textures.end();
    }
    std::unordered_map<int, Texture>::const_iterator end() const
    {
        return textures.end();
    }
    std::unordered_map<int, Texture>::const_iterator cend() const
    {
        return textures.cend();
    }

   private:
    std::unordered_map<int, Texture> textures;
};
