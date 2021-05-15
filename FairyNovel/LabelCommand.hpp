#ifndef LABELCOMMAND_HPP
#define LABELCOMMAND_HPP

#include "Command.hpp"

class LabelCommand : public Command
{
public:
	LabelCommand(const std::string& identifier, const std::string& args);
	~LabelCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;
};


#endif