#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include "ResourceIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


class MusicPlayer : private sf::NonCopyable
{
public:
	MusicPlayer();

	void play(std::string& id);
	void stop();

	void setPaused(bool paused);

	bool isMusicPlaying() const;

	sf::Time getCurrentMusicOffset() const;
	void setCurrentMusicOffset(sf::Time time);

	std::string getCurrentMusic() const;

	void addMusic(std::string& id, std::string& path);

	void setVolume(float amount);
	float getVolume() const;

private:
	sf::Music nMusic;
	std::string nCurrentMusic;

	std::map<std::string, std::string> nFileNames;

	float nVolume;
};

#endif