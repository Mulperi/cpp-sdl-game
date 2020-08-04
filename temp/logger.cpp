#include <string>
#include <iostream>
#include "logger.h"

Logger::Logger() {}
Logger::~Logger() {}
void Logger::log(std::string str)
{
    if (active)
    {
        std::cout << str << std::endl;
    }
}
