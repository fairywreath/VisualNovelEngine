#ifndef DISPLAYTEXTCOMMAND_HPP
#define DISPLAYTEXTCOMMAND_HPP

#include <SFML/System/Vector2.hpp>

#include "Command.hpp"

class DisplayTextCommand : public Command
{
public:
	DisplayTextCommand(Type type, const std::string& identifier, const std::string& arguments);
	virtual ~DisplayTextCommand();

	virtual void execute(Engine& engine) override;
	virtual std::vector<std::string> getArguments() const override;

};

#endif
