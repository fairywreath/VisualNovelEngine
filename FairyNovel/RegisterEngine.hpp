#ifndef REGISTERENGINE_HPP
#define REGISTERENGINE_HPP

#include "ResourceIdentifiers.hpp"
#include "ResourceManager.hpp"
#include "SoundPlayer.hpp"
#include "MusicPlayer.hpp"

// #include "CharacterManager.hpp"

#include "Command.hpp"

class RegisterEngine
{
public:
	RegisterEngine(TextureManager& textures, FontManager& fonts, SoundPlayer& sounds, MusicPlayer& music);

	~RegisterEngine() = default;
	RegisterEngine(const RegisterEngine&) = delete;
	RegisterEngine& operator=(const RegisterEngine&) = delete;

	void runCommand(Command* command);

private:
	TextureManager& nTextures;
	FontManager& nFonts;
	SoundPlayer& nSoundPlayer;
	MusicPlayer& nMusicPlayer;

};

#endif

