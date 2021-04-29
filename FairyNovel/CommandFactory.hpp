#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "Command.hpp"

#include <memory>

class CommandFactory
{
public:
	typedef std::unique_ptr<Command> CommandPtr;

public:
	CommandPtr generateCommand(const std::string& kw, const std::string& id, const std::string& args, bool reg=false);

private:

};

#endif

