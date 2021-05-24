#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <iostream>
#include <string>

#include <SFML/System/Clock.hpp>
#include <SFML/System/NonCopyable.hpp>

#define LOGGER Logger::GetLogger()

// Logger singleton class
class Logger
{
public:
    void Log(const std::string& tag, std::string& message);
    Logger& operator << (const std::string& message);

    static void SetLogger(std::string& logPath);
    static Logger* GetLogger();

private:
    Logger();

    static std::string nFileName;
    static Logger* nThis;
    static std::ofstream nLogfile;
    static sf::Clock nClock;

};

#endif
