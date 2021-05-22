#ifndef BLURENTITYCOMMAND_HPP
#define BLURENTITYCOMMAND_HPP

#include "Command.hpp"

class BlurEntityCommand : public Command
{
public:
	BlurEntityCommand(const std::string& id, const std::string& args);
	~BlurEntityCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;


};

#endif