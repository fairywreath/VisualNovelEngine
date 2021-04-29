#include "Command.hpp"

#include "Utility.hpp"
#include <iostream>


Command::Command(Type type, const std::string& identifier, const std::string& arguments) :
	nType(type),
	nIdentifier(identifier),
	nArguments(arguments)
{
	// std::cout << "created command of type: " <<  (int)nType << std::endl;
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


