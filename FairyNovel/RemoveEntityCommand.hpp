#ifndef REMOVEENTITYCOMMAND_HPP
#define REMOVEENTITYCOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class RemoveEntityCommand : public Command
{
public:
	RemoveEntityCommand(const std::string& identifier, const std::string& arguments);
	~RemoveEntityCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

private:
	float fadeTime;		// later add implementations
};

#endif