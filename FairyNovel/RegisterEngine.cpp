#include "RegisterEngine.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <iostream>

RegisterEngine::RegisterEngine(TextureManager& textures, FontManager& fonts, 
	SoundPlayer& sounds, MusicPlayer& music, std::unordered_map<std::string, CharacterBlueprint>& characters) :
	nTextures(textures),
	nFonts(fonts),
	nSoundPlayer(sounds),
	nMusicPlayer(music),
	nCharacters(characters)
{
}

void RegisterEngine::runCommand(Command* command)
{
	if (command == nullptr) return;

	switch (command->getType())
	{
	case Command::Type::RegisterTexture: 
	{
		nTextures.load(command->getIdentifier(), command->getArgumentString());
		break;
	}
	case Command::Type::RegisterFont:
	{
		nFonts.load(command->getIdentifier(), command->getArgumentString());
		break;
	}
	case Command::Type::RegisterMusic:
	{
		nMusicPlayer.addMusic(command->getIdentifier(), command->getArgumentString());
		break;
	}
	case Command::Type::RegisterSE:
	{
		nSoundPlayer.addSound(command->getIdentifier(), command->getArgumentString());
		break;
	}
	case Command::Type::RegisterCharacter:
	{
		registerCharacter(command->getIdentifier(), command->getArgumentString());
		break;
	}
	default:
		break;
	}
}

void RegisterEngine::registerCharacter(const std::string& id, const std::string& args)
{
	std::vector<std::string> arg = Util::split(args, ';');
	assert(arg.size() == 2);
	for (auto& ar : arg)
	{
		ar = Util::trim(ar);
	}
	
	if (!nTextures.contains(arg[1]))
	{
		// log error here
		return;
	}
	
	if (nCharacters.find(id) == nCharacters.end())
	{
		nCharacters.insert(std::make_pair(id, CharacterBlueprint(id, arg[0], arg[1], nTextures)));
	}
	else
	{
		nCharacters.at(id).insertState(arg[0], arg[1]);
	}
}
