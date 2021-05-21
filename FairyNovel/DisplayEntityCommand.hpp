#ifndef DISPLAYENTITYCOMMAND_HPP
#define DISPLAYENTITYCOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class DisplayEntityCommand : public Command
{
public:
	DisplayEntityCommand(const std::string& identifier, const std::string& arguments);
	
	~DisplayEntityCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

private:
	sf::Vector2f nPosition;
};


#endif

