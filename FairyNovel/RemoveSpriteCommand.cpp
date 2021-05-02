#include "RemoveSpriteCommand.hpp"
#include "Engine.hpp"

RemoveSpriteCommand::RemoveSpriteCommand(Type type, const std::string& identifier,
	const std::string& arguments) :
	Command(type, identifier, arguments),
	fadeTime(0)
{
}

RemoveSpriteCommand::~RemoveSpriteCommand()
{
}

void RemoveSpriteCommand::execute(Engine& engine)
{
	// possibly change including extra args later
	engine.removeEntity(getIdentifier());
}

std::vector<std::string> RemoveSpriteCommand::getArguments() const
{
	// possible break it down later including fade time
	return std::vector<std::string>{getIdentifier()};
}
