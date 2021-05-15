#ifndef PLAYSOUNDCOMMAND_HPP
#define PLAYSOUNDCOMMAND_HPP

#include "Command.hpp"

class PlaySoundCommand : public Command
{
public:
	PlaySoundCommand(const std::string& identifier, const std::string& arguments);
	~PlaySoundCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};

#endif

