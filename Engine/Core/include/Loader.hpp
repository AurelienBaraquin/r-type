#pragma once

#include <fstream>
#include <string>
#include <vector>

class ILoader
{
   public:
    ILoader() = default;
    virtual ~ILoader() = default;

    virtual void load(const std::string& filePath) = 0;
};

class LoaderManager
{
   public:
    LoaderManager() = default;
    ~LoaderManager() = default;

    void load(std::string filePath)
    {
        for (auto& loader : _loaders)
        {
            loader->load(filePath);
        }
    }

    void addLoader(ILoader* loader)
    {
        _loaders.push_back(loader);
    }

   private:
    std::vector<ILoader*> _loaders;
};
