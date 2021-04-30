#ifndef PLAYSOUNDCOMMAND_HPP
#define PLAYSOUNDCOMMAND_HPP

#include "Command.hpp"

class PlaySoundCommand : public Command
{
public:
	PlaySoundCommand(Type type, const std::string& identifier, const std::string& arguments);
	virtual ~PlaySoundCommand();

	virtual void execute(Engine& engine) override;
	virtual std::vector<std::string> getArguments() const override;

};

#endif

