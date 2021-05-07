#ifndef MOVEENTITYCOMMAND_HPP
#define MOVEENTITYCOMMAND_HPP

#include "Command.hpp"

class MoveEntityCommand : public Command
{
public:
	MoveEntityCommand(const std::string& id, const std::string& args);
	virtual ~MoveEntityCommand();

	virtual void execute(Engine& engine) override;
	virtual std::vector<std::string> getArguments() const override;

};


#endif