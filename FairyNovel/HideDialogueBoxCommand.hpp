#ifndef HIDEDIALOGUEBOXCOMMAND_HPP
#define HIDEDIALOGUEBOXCOMMAND_HPP

#include "Command.hpp"

class HideDialogueBoxCommand : public Command
{
public:
	HideDialogueBoxCommand(const std::string& id, const std::string& args);
	~HideDialogueBoxCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};



#endif