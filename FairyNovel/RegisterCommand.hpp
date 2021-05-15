#ifndef REGISTERCOMMAND_HPP
#define REGISTERCOMMAND_HPP

#include "Command.hpp"

class Engine;

class RegisterCommand : public Command
{
public:
	RegisterCommand(Command::Type type, const std::string& identifier, const std::string& arguments);
	~RegisterCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;
};

#endif