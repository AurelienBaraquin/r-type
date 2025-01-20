#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Log.hpp"

class ILoader
{
   public:
    ILoader()
    {
        std::cout << "ILoader constructor" << std::endl;
    }
    virtual ~ILoader() = default;

    virtual void load(const nlohmann::json& data) = 0;
    virtual std::string getPart() = 0;
    virtual std::vector<ILoader*> getLoaders()
    {
        return {};
    }
};

class LoaderManager
{
   public:
    LoaderManager() = default;
    ~LoaderManager() = default;

    void load(const nlohmann::json& data)
    {
        for (auto& loader : _loaders) {
            std::cout << "Loading: " << loader->getPart() << std::endl;
            if (data.find(loader->getPart()) != data.end()) {
                loader->load(data[loader->getPart()]);
            } else {
                std::cout << "No data for: " << loader->getPart() << std::endl;
            }
        }
    }

    void addLoader(ILoader* loader)
    {
        _loaders.push_back(loader);
        for (auto& subLoader : loader->getLoaders()) {
            addLoader(subLoader);
        }
    }

   private:
    std::vector<ILoader*> _loaders;
};
