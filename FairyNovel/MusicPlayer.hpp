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

	~MusicPlayer() = default;
	MusicPlayer(const MusicPlayer&) = delete;
	MusicPlayer& operator=(const MusicPlayer&) = delete;

	void play(const std::string& id);
	void stop();

	void setPaused(bool paused);

	bool isMusicPlaying() const;

	sf::Time getCurrentMusicOffset() const;
	void setCurrentMusicOffset(const sf::Time& time);

	std::string getCurrentMusic() const;

	void addMusic(const std::string& id, const std::string& path);
	bool find(const std::string& id) const;

	void setVolume(float amount);
	float getVolume() const;

private:
	sf::Music nMusic;
	std::string nCurrentMusic;

	std::map<std::string, std::string> nFileNames;

	float nVolume;
};

#endif