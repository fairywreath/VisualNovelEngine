#include "Command.hpp"

#include "Utility.hpp"

Command::Command(Type type, const std::string& identifier, const std::string& arguments) :
	nType(type),
	nIdentifier(identifier),
	nArguments()
{
	
}

Command::~Command()
{
}

Command::Type Command::getType() const
{
	return nType;
}

const std::string& Command::getIdentifier() const
{
	return nIdentifier;
}

std::string Command::getArgumentString() const
{
	return nArguments;
}


