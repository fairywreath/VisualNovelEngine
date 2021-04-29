#include "MusicPlayer.hpp"

#include <stdexcept>

MusicPlayer::MusicPlayer() :
	nMusic(),
	nFileNames(),
	nCurrentMusic("None"),
	nVolume(60.f)		
{
	// mapping the music files 
//	nFileNames[Music::Main] = "Media/Music/MainTheme.ogg";
//	nFileNames[Music::Secondary] = "Media/Music/SecondaryTheme.ogg";
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

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		nMusic.pause();
	else
		nMusic.play();
}

bool MusicPlayer::isMusicPlaying() const
{
	if (nMusic.getStatus() == sf::Music::Status::Playing)
		return true;
	else
		return false;
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