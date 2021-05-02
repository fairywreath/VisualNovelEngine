#ifndef LABELCOMMAND_HPP
#define LABELCOMMAND_HPP

#include "Command.hpp"

class LabelCommand : public Command
{
public:
	LabelCommand(const std::string& identifier, const std::string& args);
	virtual ~LabelCommand();

	virtual void execute(Engine& engine);
	virtual std::vector<std::string> getArguments() const;
};


#endif