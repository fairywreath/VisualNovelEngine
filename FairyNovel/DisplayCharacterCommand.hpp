#ifndef DISPLAYCHARACTERCOMMAND_HPP
#define DISPLAYCHARACTERCOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class DisplayCharacterCommand : public Command
{
public:
	DisplayCharacterCommand(const std::string& identifier, const std::string& arguments);

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;
};


#endif

