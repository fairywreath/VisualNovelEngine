#ifndef PLAYMUSICCOMMAND_HPP
#define PLAYMUSICCOMMAND_HPP

#include "Command.hpp"

class PlayMusicCommand : public Command
{
public:
	PlayMusicCommand(Type type, const std::string& identifier, const std::string& arguments);
	virtual ~PlayMusicCommand();

	virtual void execute(Engine& engine) override;
	virtual std::vector<std::string> getArguments() const override;

};

#endif

