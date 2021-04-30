#include "PlayMusicCommand.hpp"
#include "Engine.hpp"

PlayMusicCommand::PlayMusicCommand(Type type, const std::string& identifier, const std::string& arguments)
	: Command(type, identifier, arguments)
{
}

PlayMusicCommand::~PlayMusicCommand()
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
