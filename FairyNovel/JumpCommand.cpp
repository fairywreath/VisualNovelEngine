#include "JumpCommand.hpp"

JumpCommand::JumpCommand(const std::string& identifier, const std::string& args) :
	Command(Command::Type::Jump, identifier, args)
{
}

JumpCommand::~JumpCommand()
{
}

void JumpCommand::execute(Engine& engine)
{
	// do nothing
}

std::vector<std::string> JumpCommand::getArguments() const
{
	return std::vector<std::string>({ getArgumentString() });
}
