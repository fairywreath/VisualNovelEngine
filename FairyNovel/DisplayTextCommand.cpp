#include "DisplayTextCommand.hpp"
#include "Engine.hpp"

DisplayTextCommand::DisplayTextCommand(Type type, const std::string& identifier, 
	const std::string& arguments) :
	Command(type, identifier, arguments)
{
}

DisplayTextCommand::~DisplayTextCommand()
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
