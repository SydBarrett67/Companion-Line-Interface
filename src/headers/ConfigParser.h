#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>

class ConfigParser
{
private:
    std::map<std::string, std::size_t> cfg;

public:
    ConfigParser(std::string cfgPath);

    const std::map<std::string, std::size_t> getConfig() const;

    void loadPets(std::string path, std::vector<Pet> *pets);

    ~ConfigParser();
};
