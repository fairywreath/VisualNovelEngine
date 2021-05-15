#include "LabelCommand.hpp"

LabelCommand::LabelCommand(const std::string& identifier, const std::string& args) :
	Command(Command::Type::Label, identifier, args)
{
}

void LabelCommand::execute(Engine& engine)
{
	// do nothing for a command, simply go to next command??
}

std::vector<std::string> LabelCommand::getArguments() const
{
	return std::vector<std::string>({ getArgumentString() });
}
