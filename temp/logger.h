#ifndef LOGGER_H
#define LOGGER_H
#include <string>

class Logger
{
public:
    bool active;

    Logger();
    ~Logger();
    void log(std::string str);
};
#endif