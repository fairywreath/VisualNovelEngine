#include "RegisterEngine.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

RegisterEngine::RegisterEngine(TextureManager& textures, FontManager& fonts, 
	SoundPlayer& sounds, MusicPlayer& music) :
	nTextures(&textures),
	nFonts(&fonts),
	nSoundPlayer(&sounds),
	nMusicPlayer(&music)
{
}

void RegisterEngine::runCommand(Command* command)
{
	switch (command->getType())
	{
	case Command::Type::RegisterTexture: 
	{
		nTextures->load(command->getIdentifier(), command->getArgumentString());
	}
	case Command::Type::RegisterFont:
	{
		nFonts->load(command->getIdentifier(), command->getArgumentString());
	}
	case Command::Type::RegisterMusic:
	{
		nMusicPlayer->addMusic(command->getIdentifier(), command->getArgumentString());
	}
	case Command::Type::RegisterSE:
	{
		nSoundPlayer->addSound(command->getIdentifier(), command->getArgumentString());
	}
	default:
		break;
	}
}
