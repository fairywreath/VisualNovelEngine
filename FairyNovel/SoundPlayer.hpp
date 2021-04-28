#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <list>

class SoundPlayer : private sf::NonCopyable
{
public:
	SoundPlayer();

	void play(std::string& id);
	void play(std::string& id, sf::Vector2f position);
	
	void removeStoppedSounds();
	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

	void addSound(std::string& id, std::string& path);

	void setVolume(float amount);
	float getVolume() const;

private:
	SoundBufferManager nSoundBuffers;
	float nVolume;
	std::list<sf::Sound> nSounds;

};

#endif

