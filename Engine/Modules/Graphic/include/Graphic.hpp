#pragma once

#include "ISystem.hpp"
#include <string>

class Graphic : public ISystem
{
   public:
    Graphic(std::string title, int width, int height) : _title(title), _width(width), _height(height)
    {
    }

    ~Graphic() override = default;

    void startup() override;
    void update(float deltaTime) override;
    void shutdown() override;

   private:
    std::string _title;
    int _width;
    int _height;
};
