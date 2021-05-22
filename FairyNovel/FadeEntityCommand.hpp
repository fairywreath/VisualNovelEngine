#ifndef FADEENTITYCOMMAND_HPP
#define FADEENTITYCOMMAND_HPP

#include "Command.hpp"

class FadeEntityCommand : public Command
{
public:
	FadeEntityCommand(const std::string& id, const std::string& args);
	~FadeEntityCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};

#endif