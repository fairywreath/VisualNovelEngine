#include "SoundPlayer.hpp"

#include <SFML/Audio/Listener.hpp>

#include <cmath>
#include <iostream>

namespace
{
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

SoundPlayer::SoundPlayer() :
	nSoundBuffers(),
	nSounds(),
	nVolume(DefaultVolume)
{
	// load SEs to the manager
	
	// set listener to point towards the screen
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}


// play the sound; add to list and play the last element
void SoundPlayer::play(const std::string& effect)
{
	play(effect, getListenerPosition());
}


// play with given position
void SoundPlayer::play(const std::string& effect, sf::Vector2f position)
{
	nSounds.push_back(sf::Sound());
	sf::Sound& sound = nSounds.back();

	sound.setBuffer(nSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);
	sound.setVolume(nVolume);

	sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
	nSounds.remove_if([](const sf::Sound& sound) {
		return sound.getStatus() == sf::Sound::Stopped;
	});
}


void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}

void SoundPlayer::addSound(const std::string& id, const std::string& path)
{
	nSoundBuffers.load(id, path);
}

bool SoundPlayer::find(const std::string& id) const
{
	// TODO: add find functionality
	return false;
}

void SoundPlayer::setVolume(float amount)
{
	if (amount >= 0.f && amount <= 100.f)
	{
		nVolume = amount;
		std::cout << "new amount: " << amount << std::endl;
	}
}

float SoundPlayer::getVolume() const
{
	return nVolume;
}

void SoundPlayer::setupDefault()
{
	setVolume(DefaultVolume);
}

