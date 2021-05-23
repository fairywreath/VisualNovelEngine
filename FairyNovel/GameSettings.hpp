#ifndef GAMESETTINGS_HPP
#define GAMESETTINGS_HPP

#include "state.hpp"

/*
	@possible publisher class? maybe a strut is better
*/
class GameSettings
{
public:
	GameSettings();

	void sendEvents();

	bool isChanged() const;

	/*
		@game engine settings
	*/
	bool AutoMode;
	float DialogueBoxOpactiy;
	int DialogueSpeed;
	int AutoDelaySpeed;

	/*
		@TODO
	*/
	bool ContinueVoicePlaybackOnLine;
	bool VoiceVolume;
	bool ReadSkip;
	bool AllSkip;

	/*
		@list of subscribers and events?
	*/

	/*
		@list of chaacter voices volumes?
	*/
private:
	bool nChanged;
};



#endif