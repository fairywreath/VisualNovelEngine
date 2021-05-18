#include "Command.hpp"

#include "Utility.hpp"
#include <iostream>


Command::Command(Type type, const std::string& identifier, const std::string& arguments) :
	nType(type),
	nIdentifier(identifier),
	nArguments(arguments)
{

}

Command::Type Command::getType() const
{
	return nType;
}

std::string Command::getIdentifier() const
{
	return nIdentifier;
}

std::string Command::getArgumentString() const
{
	return nArguments;
}

void Command::LoggerLog(const std::string& msg) const
{
}


