#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "Command.hpp"

#include <memory>

class CommandFactory
{
public:
	using CommandPtr =  std::unique_ptr<Command>;

public:
	CommandPtr generateCommand(const std::string& kw, const std::string& id, const std::string& args);
	CommandPtr generateRegCommand(const std::string& kw, const std::string& id, const std::string& args);

private:
	void throwError(const std::string& tag, const std::string& msg);
};

#endif

