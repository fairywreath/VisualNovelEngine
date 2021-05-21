#ifndef SHOWDIALOGUEBOXCOMMAND_HPP
#define SHOWDIALOGUEBOXCOMMAND_HPP

#include "Command.hpp"

class ShowDialogueBoxCommand : public Command
{
public:
	ShowDialogueBoxCommand(const std::string& id, const std::string& args);
	~ShowDialogueBoxCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};



#endif

