#include "PlayMusicCommand.hpp"
#include "Engine.hpp"

PlayMusicCommand::PlayMusicCommand(const std::string& identifier, const std::string& arguments)
	: Command(Type::PlayMusic, identifier, arguments)
{
}

void PlayMusicCommand::execute(Engine& engine)
{
	engine.playMusic(getIdentifier());
}

std::vector<std::string> PlayMusicCommand::getArguments() const
{
	return std::vector<std::string>({ getIdentifier() });
}
