#include "RegisterCommand.hpp"
#include "Engine.hpp"

RegisterCommand::RegisterCommand(Command::Type type,const std::string& identifier, const std::string& arguments) :
	Command(type, identifier, arguments)
{
}

void RegisterCommand::execute(Engine& engine)
{
}

std::vector<std::string> RegisterCommand::getArguments() const
{
	return std::vector<std::string>();
}
