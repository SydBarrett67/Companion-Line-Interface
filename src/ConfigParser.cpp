#include <iostream>
#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string cfgPath)
{
    std::ifstream file(cfgPath);

    std::cout << "Trying to open: " << cfgPath << "\n";

    if (!file.is_open())
    {
        std::cout << "File non aperto\n";
    }

    std::string line = "";
    while(std::getline(file, line)) {
        
        size_t pos = line.find('=');
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        cfg[key] = stoi(value);
    }
}

const std::map<std::string, int> ConfigParser::getConfig() const{
    return this->cfg;
}

ConfigParser::~ConfigParser() {

}