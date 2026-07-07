#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

class Logger
{
private:
    std::fstream logFile;
    std::fstream statsFile;
    
public:
    Logger(std::string logPath, std::string statsFile);

    // Log to file
    void log(std::string line, int maxLines = 50);
    void stats(std::map<std::string, std::size_t>);

    ~Logger();
};