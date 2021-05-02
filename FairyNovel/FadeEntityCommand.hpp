#ifndef FADEENTITYCOMMAND_HPP
#define FADEENTITYCOMMAND_HPP

#include "Command.hpp"

class FadeEntityCommand : public Command
{
public:
	FadeEntityCommand(const std::string& id, const std::string& args);
	virtual ~FadeEntityCommand();

	virtual void execute(Engine& engine) override;
	virtual std::vector<std::string> getArguments() const override;

private:
	bool isNumber(const std::string& str);

};

#endif