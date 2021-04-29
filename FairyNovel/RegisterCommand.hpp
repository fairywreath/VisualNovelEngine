#ifndef REGISTERCOMMAND_HPP
#define REGISTERCOMMAND_HPP

#include "Command.hpp"

class RegisterCommand : public Command
{
public:
	RegisterCommand(Command::Type type, const std::string& identifier, const std::string& arguments);


};

#endif