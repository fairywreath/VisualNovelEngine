#ifndef REGISTERENGINE_HPP
#define REGISTERENGINE_HPP

#include "ResourceIdentifiers.hpp"
#include "ResourceManager.hpp"
#include "SoundPlayer.hpp"
#include "MusicPlayer.hpp"
#include "CharacterBlueprint.hpp"
#include "Command.hpp"

#include <unordered_map>

class RegisterEngine
{
public:
	RegisterEngine(TextureManager& textures, FontManager& fonts, SoundPlayer& sounds, MusicPlayer& music,
		std::unordered_map<std::string, CharacterBlueprint>& characters);

	~RegisterEngine() = default;
	RegisterEngine(const RegisterEngine&) = delete;
	RegisterEngine& operator=(const RegisterEngine&) = delete;

	void runCommand(Command* command);

private:
	void registerCharacter(const std::string& id, const std::string& args);

private:
	TextureManager& nTextures;
	FontManager& nFonts;
	SoundPlayer& nSoundPlayer;
	MusicPlayer& nMusicPlayer;

	std::unordered_map<std::string, CharacterBlueprint>& nCharacters;
};

#endif

