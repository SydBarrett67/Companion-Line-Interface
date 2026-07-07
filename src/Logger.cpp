#include "headers/Logger.h"


Logger::Logger(std::string logPath, std::string statsPath)
{
    this->logFile.open(logPath, std::ios::in | std::ios::out);
    if (!logFile.is_open()) std::cerr << "Error opening log file";
    this->statsFile.open(statsPath);
}

/*

    LOG & STATS

*/

void Logger::log(std::string toAdd, int maxLines) {
    // Read file to count lines and append
    std::vector<std::string> temp;
    std::string templine;
    int c = 0;
    this->logFile.seekg(0);
    while(std::getline(this->logFile, templine)) {
        temp.push_back(templine);
        c++;
    }
    if (c > maxLines) {
        temp.erase(temp.begin());
    }
    temp.push_back(toAdd);
    this->logFile.clear();
    this->logFile.seekp(0);
    // Write to file
    for (std::string s : temp) {
        this->logFile << s << "\n";
    }
    this->logFile.clear();
}

Logger::~Logger()
{
}
