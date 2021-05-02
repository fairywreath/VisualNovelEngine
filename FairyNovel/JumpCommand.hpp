#ifndef JUMPCOMMAND_HPP
#define JUMPCOMMAND_HPP

#include "Command.hpp"

class JumpCommand : public Command
{
public:
	JumpCommand(const std::string& identifier, const std::string& args);
	virtual ~JumpCommand();

	virtual void execute(Engine& engine);
	virtual std::vector<std::string> getArguments() const;
};


#endif