#ifndef CHARACTERMANAGER_HPP
#define CHARACTERMANAGER_HPP

#include "CharacterBlueprint.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceManager.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <unordered_map>
#include <cmath>

class CharacterManager
{
public:
	explicit CharacterManager(TextureManager& textures);
	CharacterManager(const CharacterManager&) = delete;
	CharacterManager& operator=(const CharacterManager&) = delete;

	void registerCharacter(const std::string& id, const std::string& defState, const std::string& defTexture);
	bool characterExists(const std::string& identifier);
	std::unordered_map<std::string, CharacterBlueprint>& getCharacterBlueprints();
	const CharacterBlueprint& getBlueprint(const std::string& identifier) noexcept;


	/*
		@insert character textures/states
	*/
	void insertCharacterTexture(const std::string& id, const std::string& state, const std::string& texture);

	/*
		@voice functionalities, play voice with volume
	*/
	void playVoice(const std::string& filePath);			// play using default vol
	void playVoice(const std::string& identifier, const std::string& filePath);
	void stopVoice();

	void setCharacterVolume(const std::string& identifier, float amount);
	float getCharacterVolume(const std::string& identifier) const;

	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

	bool isVoicePlaying() const;


private:
	/*
		@for voice/sounds
	*/
	static constexpr auto ListenerZ = 300.f;
	static constexpr auto Attenuation = 8.f;
	static constexpr auto MinDistance2D = 200.f;
	static constexpr auto MinDistance3D = 360.5551f;			// based on equation below
	// static constexpr auto MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
	static constexpr auto DefaultVolume = 60.f;

	sf::SoundBuffer nBuffer;
	sf::Sound nSound;

private:
	std::unordered_map<std::string, CharacterBlueprint> nCharacters;
	std::unordered_map<std::string, float> nCharacterVolumes;

	TextureManager& nTextures;
};



#endif