#include "CharacterManager.hpp"
#include "Logger.hpp"

#include <SFML/Audio/Listener.hpp>

CharacterManager::CharacterManager(TextureManager& textures) :
	nTextures(textures),
	nCharacters(),
	nCharacterVolumes()
{
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void CharacterManager::playVoice(const std::string& filePath)
{
	playVoice("", filePath);
}

void CharacterManager::playVoice(const std::string& identifier, const std::string& filePath)
{
	if (!nBuffer.loadFromFile(filePath))
	{
		// log
		return;
	}

	auto position = getListenerPosition();

	nSound.setBuffer(nBuffer);
	nSound.setPosition(position.x, -position.y, 0.f);
	nSound.setAttenuation(Attenuation);
	nSound.setMinDistance(MinDistance3D);

	if (nCharacterVolumes.find(identifier) == nCharacterVolumes.end())
	{
		// log, but play nevertheles
		nSound.setVolume(DefaultVolume);
	}
	else
	{
		nSound.setVolume(nCharacterVolumes.at(identifier));
	}


	nSound.play();
}

void CharacterManager::stopVoice()
{
	nSound.stop();
}

void CharacterManager::setCharacterVolume(const std::string& identifier, float amount)
{
	if (nCharacterVolumes.find(identifier) == nCharacterVolumes.end())
	{
		// log
		return;
	}

	nCharacterVolumes.at(identifier) = amount;
}

float CharacterManager::getCharacterVolume(const std::string& identifier) const
{
	if (nCharacterVolumes.find(identifier) == nCharacterVolumes.end())
	{
		// log, return FLT_MAX as error, kinda bad code but whatever
		return FLT_MAX;
	}

	return nCharacterVolumes.at(identifier);
}

void CharacterManager::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f CharacterManager::getListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}

bool CharacterManager::isVoicePlaying() const
{
	return (nSound.getStatus() == sf::Sound::Playing);
}

bool CharacterManager::characterExists(const std::string& identifier)
{
	return (nCharacters.find(identifier) != nCharacters.end());
}

std::unordered_map<std::string, CharacterBlueprint>& CharacterManager::getCharacterBlueprints()
{
	return nCharacters;
}

const CharacterBlueprint& CharacterManager::getBlueprint(const std::string& identifier) noexcept
{
	return nCharacters.at(identifier);
}


void CharacterManager::registerCharacter(const std::string& id, const std::string& defState, const std::string& defTexture)
{
	if (nCharacters.find(id) != nCharacters.end())
	{
		// log
		return;
	}

	nCharacters.insert(std::make_pair(id, CharacterBlueprint(id, defState, defTexture, nTextures)));
	nCharacterVolumes.insert(std::make_pair(id, DefaultVolume));
}

void CharacterManager::insertCharacterTexture(const std::string& id, const std::string& state, const std::string& texture)
{
	if (nCharacters.find(id) == nCharacters.end())
	{
		// log, character not found
		return;
	}

	nCharacters.at(id).insertState(state, texture);
}