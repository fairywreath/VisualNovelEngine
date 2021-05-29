#include "VoicePlayer.hpp"
#include "Logger.hpp"

#include <SFML/Audio/Listener.hpp>

VoicePlayer::VoicePlayer() :
	nCharacterVolumes()
{
	// will probably no need this, it clashes with the soundPlayer... whatever
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void VoicePlayer::play(const std::string& filePath)
{
	play("", filePath);
}

void VoicePlayer::play(const std::string& identifier, const std::string& filePath)
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

void VoicePlayer::stop()
{
	nSound.stop();
}

void VoicePlayer::insertCharacter(const std::string& identifier)
{
	if (nCharacterVolumes.find(identifier) != nCharacterVolumes.end())
	{
		// log, already in map
		return;
	}

	nCharacterVolumes.insert(std::make_pair(identifier, DefaultVolume));	// 60 as default vol
}

void VoicePlayer::setVolume(const std::string& identifier, float amount)
{
	if (nCharacterVolumes.find(identifier) == nCharacterVolumes.end())
	{
		// log
		return;
	}

	nCharacterVolumes.at(identifier) = amount;
}

float VoicePlayer::getVolume(const std::string& identifier) const
{
	if (nCharacterVolumes.find(identifier) == nCharacterVolumes.end())
	{
		// log, return FLT_MAX as error, kinda bad code but whatever
		/*
			@can be assumed to be safe because this function will only be called
			based on the charactermap
			@maybe it's better to use character manager for both playing the voice and storing
			character metadata??????
		*/
		return FLT_MAX;
	}

	return nCharacterVolumes.at(identifier);
}

void VoicePlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f VoicePlayer::getListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}
