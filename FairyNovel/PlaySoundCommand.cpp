#include "PlaySoundCommand.hpp"
#include "Engine.hpp"

PlaySoundCommand::PlaySoundCommand(const std::string& identifier, const std::string& arguments)
	:Command(Type::PlaySound, identifier, arguments)
{
}

void PlaySoundCommand::execute(Engine& engine)
{
	engine.playSound(getIdentifier());
}

std::vector<std::string> PlaySoundCommand::getArguments() const
{
	return std::vector<std::string>{getIdentifier()};
}
