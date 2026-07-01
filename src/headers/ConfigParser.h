#pragma once

#include <string>
#include <map>
#include <fstream>

class ConfigParser
{
private:
    std::map<std::string, int> cfg;


public:
    ConfigParser(std::string cfgPath);

    const std::map<std::string, int> getConfig() const;

    ~ConfigParser();
};
