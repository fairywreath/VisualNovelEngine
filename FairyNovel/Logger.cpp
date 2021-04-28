#include "Logger.hpp"

#include <cassert>

// initialize static class members
Logger* Logger::nThis = nullptr;	
std::string Logger::nFileName = "logs/novel.log";		// default log path
std::ofstream Logger::nLogfile;
sf::Clock Logger::nClock;

Logger::Logger() 
{
}

void Logger::SetLogger(std::string& logPath)
{
	assert(nThis == nullptr);
	nFileName = logPath;

	nThis = new Logger();
	nLogfile.open(nFileName, std::ios::out);
}

Logger* Logger::GetLogger()
{
	assert(nThis != nullptr);
	return nThis;
}

void Logger::Log(const std::string& tag, std::string& message)
{
	nLogfile << "[" << "tag" << " at " << nClock.getElapsedTime().asSeconds() << "s] " << message << "\n";
}

Logger& Logger::operator << (const std::string& message)
{
	nLogfile << "[" << "Default" << " at " << nClock.getElapsedTime().asSeconds() << "s] " << message << "\n";
	return *this;
}

