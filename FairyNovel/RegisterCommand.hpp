#ifndef REGISTERCOMMAND_HPP
#define REGISTERCOMMAND_HPP

#include "Command.hpp"

class Engine;

class RegisterCommand : public Command
{
public:
	RegisterCommand(Command::Type type, const std::string& identifier, const std::string& arguments);

	virtual void execute(Engine& engine) override;
	virtual std::vector<std::string> getArguments() override;
};

#endif