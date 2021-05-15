#ifndef REMOVESPRITECOMMAND_HPP
#define REMOVESPRITECOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class RemoveSpriteCommand : public Command
{
public:
	RemoveSpriteCommand(const std::string& identifier, const std::string& arguments);
	~RemoveSpriteCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

private:
	float fadeTime;		// later add implementations
};

#endif