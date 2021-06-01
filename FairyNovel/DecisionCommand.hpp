#ifndef DECISIONCOMMAND_HPP
#define DECISIONCOMMAND_HPP

#include "Command.hpp"

class DecisionCommand : public Command
{
public:
	DecisionCommand(const std::string& identifier, const std::string& args);

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

private:
	std::vector<std::pair<std::string, std::string>> nDecisions;

};

#endif