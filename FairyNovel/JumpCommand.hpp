#ifndef JUMPCOMMAND_HPP
#define JUMPCOMMAND_HPP

#include "Command.hpp"

class JumpCommand : public Command
{
public:
	JumpCommand(const std::string& identifier, const std::string& args);
	~JumpCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;
};


#endif