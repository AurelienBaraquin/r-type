#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "Log.hpp"

class ILoader
{
   public:
    ILoader() = default;
    virtual ~ILoader() = default;

    virtual void load(const nlohmann::json& data) = 0;
    virtual std::string getPart() = 0;
    virtual std::vector<ILoader*> getLoaders() { return {}; }
};

class LoaderManager
{
   public:
    LoaderManager() = default;
    ~LoaderManager() = default;

    void load(const nlohmann::json& data)
    {
        for (auto& loader : _loaders)
        {
            if (data.find(loader->getPart()) != data.end())
            {
                loader->load(data[loader->getPart()]);
            }
        }
    }

    void addLoader(ILoader* loader)
    {
        Logger::getInstance().info("Adding loader: " + loader->getPart());
        _loaders.push_back(loader);
        for (auto& subLoader : loader->getLoaders())
        {
            addLoader(subLoader);
        }
    }

   private:
    std::vector<ILoader*> _loaders;
};
