#include "RegisterEngine.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <iostream>

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
	if (command == nullptr) return;

	// std::cout << command->getIdentifier() << std::endl;
	switch (command->getType())
	{
	case Command::Type::RegisterTexture: 
	{
		// std::cout << "New Texture: " << command->getIdentifier() << " Path: " << command->getArgumentString();
		nTextures->load(command->getIdentifier(), command->getArgumentString());
		break;
	}
	case Command::Type::RegisterFont:
	{
		nFonts->load(command->getIdentifier(), command->getArgumentString());
		break;
	}
	case Command::Type::RegisterMusic:
	{
		// std::cout << "New Music: " << command->getIdentifier() << " Path: " << command->getArgumentString();
		nMusicPlayer->addMusic(command->getIdentifier(), command->getArgumentString());
		break;
	}
	case Command::Type::RegisterSE:
	{
		nSoundPlayer->addSound(command->getIdentifier(), command->getArgumentString());
		break;
	}
	default:
		break;
	}
}
