#include "RemoveEntityCommand.hpp"
#include "Engine.hpp"

RemoveEntityCommand::RemoveEntityCommand(const std::string& identifier,
	const std::string& arguments) :
	Command(Type::RemoveEntity, identifier, arguments),
	fadeTime(0)
{
}


void RemoveEntityCommand::execute(Engine& engine)
{
	// possibly change including extra args later
	engine.removeEntity(getIdentifier());
}

std::vector<std::string> RemoveEntityCommand::getArguments() const
{
	// possible break it down later including fade time
	return std::vector<std::string>{getIdentifier()};
}
