#ifndef DISPLAYBACKGROUNDCOMMAND_HPP
#define DISPLAYBACKGROUNDCOMMAND_HPP

#include "Command.hpp"

class DisplayBackgroundCommand : public Command
{
public:
	DisplayBackgroundCommand(const std::string& id, const std::string& args);
	~DisplayBackgroundCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};


#endif