#include "MusicPlayer.hpp"

#include <stdexcept>

#include <iostream>

MusicPlayer::MusicPlayer() :
	nMusic(),
	nFileNames(),
	nCurrentMusic("None"),
	nVolume(DefaultVolume),
	nStartVolume(DefaultVolume),
	nInFade(false),
	nFadeElapsed(sf::Time::Zero),
	nFadeDuration(0.f),
	nTargetVolume(0.f)
{

}

void MusicPlayer::play(const std::string& id)
{
	if (nFileNames.find(id) == nFileNames.end())
		throw std::runtime_error("Music ID does not exist in Map: " + id);

	// trhow exception if it does not exist 
	std::string filename = nFileNames.at(id);

	if (!nMusic.openFromFile(filename))
		throw std::runtime_error("Music: " + filename + " could not be loaded.");

	nMusic.setVolume(nVolume);
	nMusic.setLoop(true);
	nMusic.play();

	nCurrentMusic = id;
}

void MusicPlayer::stop()
{
	nMusic.stop();
	nCurrentMusic = "None";
}

void MusicPlayer::fadeOut(float time)
{
	nInFade = true;
	nTargetVolume = 0;
	nStartVolume = nVolume;
	nFadeDuration = time;
}

void MusicPlayer::fadeIn(float time)
{
	nInFade = true;
	nTargetVolume = nVolume;
	nStartVolume = 0;
	nFadeDuration = time;
}

void MusicPlayer::update(sf::Time dt)
{
	if (nInFade)
	{
		nFadeElapsed += dt;
		if (nFadeElapsed.asSeconds() >= nFadeDuration)
		{
			nInFade = false;
			nMusic.setVolume(nTargetVolume);
			nFadeElapsed = sf::Time::Zero;
		}
		else
		{
			float volume = (float)nStartVolume + ((float)(nTargetVolume - nStartVolume)
				* nFadeElapsed.asSeconds() / nFadeDuration);
			nMusic.setVolume(volume);
		}
	}
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		nMusic.pause();
	else
		nMusic.play();
}

bool MusicPlayer::isMusicPlaying() const
{
	return (nMusic.getStatus() == sf::Music::Status::Playing);
}

std::string MusicPlayer::getCurrentMusic() const
{
	return nCurrentMusic;
}

void MusicPlayer::addMusic(const std::string& id, const std::string& path)
{
	if (nFileNames.find(id) != nFileNames.end())
		throw std::runtime_error("Redefinition of music ID: " + id);

	nFileNames.insert(std::make_pair(id, path));
}

bool MusicPlayer::find(const std::string& id) const
{
	if (nFileNames.find(id) != nFileNames.end()) return true;
	return false;
}

sf::Time MusicPlayer::getCurrentMusicOffset() const
{
	return nMusic.getPlayingOffset();
}

void MusicPlayer::setCurrentMusicOffset(const sf::Time& offset)
{
	nMusic.setPlayingOffset(offset);
}

void MusicPlayer::setVolume(float amount)
{
	if (nInFade)
	{
		nInFade = false;
		nFadeElapsed = sf::Time::Zero;
	}

	// if amount is not in range leave it be
	if ((amount) >= 0.f && (amount) <= 100.f)
	{
		nVolume = amount;
		nMusic.setVolume(nVolume);
	}
}

float MusicPlayer::getVolume() const
{
	return nVolume;
}

void MusicPlayer::setupDefault()
{
	setVolume(DefaultVolume);
}