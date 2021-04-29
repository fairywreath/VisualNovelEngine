#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "Command.hpp"

#include <memory>

class CommandFactory
{
public:
	typedef std::unique_ptr<Command> CommandPtr;

public:
	CommandPtr generateCommand(const std::string& kw, const std::string& id, const std::string& args);
	CommandPtr generateRegCommand(const std::string& kw, const std::string& id, const std::string& args);

private:
	void throwError(const std::string& tag, const std::string& msg);
};

#endif

