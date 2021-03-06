#include "DisplayTextCommand.hpp"
#include "Engine.hpp"

#include <iostream>

DisplayTextCommand::DisplayTextCommand(const std::string& identifier, 
	const std::string& arguments) :
	Command(Type::DisplayText, identifier, arguments)
{
}

void DisplayTextCommand::execute(Engine& engine)
{
	// possibly change including extra args later
	engine.displayText(getArgumentString(), getIdentifier());
}

std::vector<std::string> DisplayTextCommand::getArguments() const
{
	// possible break it down later including fade time
	return std::vector<std::string>{getIdentifier()};
}
