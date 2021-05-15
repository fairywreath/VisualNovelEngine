#ifndef PLAYMUSICCOMMAND_HPP
#define PLAYMUSICCOMMAND_HPP

#include "Command.hpp"

class PlayMusicCommand : public Command
{
public:
	PlayMusicCommand(const std::string& identifier, const std::string& arguments);
	~PlayMusicCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};

#endif

