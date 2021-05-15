#ifndef DISPLAYSPRITECOMMAND_HPP
#define DISPLAYSPRITECOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class DisplaySpriteCommand : public Command
{
public:
	DisplaySpriteCommand(const std::string& identifier, const std::string& arguments);
	
	~DisplaySpriteCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

private:
	sf::Vector2f nPosition;
};


#endif

