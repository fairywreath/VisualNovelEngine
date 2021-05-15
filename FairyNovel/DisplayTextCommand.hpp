#ifndef DISPLAYTEXTCOMMAND_HPP
#define DISPLAYTEXTCOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class DisplayTextCommand : public Command
{
public:
	DisplayTextCommand(const std::string& identifier, const std::string& arguments);
	~DisplayTextCommand() override = default;

	void execute(Engine& engine) override;
	std::vector<std::string> getArguments() const override;

};

#endif
