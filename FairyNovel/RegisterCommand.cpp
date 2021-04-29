#include "RegisterCommand.hpp"

RegisterCommand::RegisterCommand(Command::Type type,const std::string& identifier, const std::string& arguments) :
	Command(type, identifier, arguments)
{
}
