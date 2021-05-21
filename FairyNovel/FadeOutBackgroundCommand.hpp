#ifndef FADEOUTBACKGROUNDCOMMAND_HPP
#define FADEOUTBACKGROUNDCOMMAND_HPP

#include "Command.hpp"

class FadeOutBackgroundCommand : public Command
{
public:
	FadeOutBackgroundCommand(const std::string& id, const std::string& args);
	~FadeOutBackgroundCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};


#endif