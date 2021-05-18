#ifndef CHARACTERSTATECOMMAND_HPP
#define CHARACTERSTATECOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class CharacterStateCommand : public Command
{
public:
	CharacterStateCommand(const std::string& identifier, const std::string& arguments);

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;
};


#endif

