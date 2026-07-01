#include <iostream>
#include "headers/ConfigParser.h"

ConfigParser::ConfigParser(std::string cfgPath)
{
    try {
        std::ifstream file(cfgPath);

        std::string line = "";
        while(std::getline(file, line)) {
            size_t pos = line.find('=');
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            cfg[key] = stoi(value);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error opening config file: " << e.what() << "\n";
        return;
    }
    
}

const std::map<std::string, int> ConfigParser::getConfig() const{
    return this->cfg;
}

ConfigParser::~ConfigParser() {

}