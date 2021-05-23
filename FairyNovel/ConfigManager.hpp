#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

/*
	@possible publisher class? maybe a strut is better
*/

class Engine;

class ConfigManager
{
public:
	ConfigManager();
	ConfigManager(const ConfigManager&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;

	void applySettings(Engine& engine);

	/*
		@getters?
	*/
	bool getAutoMode() const;
	float getTextWindowTrans() const;
	int getMessageSpeed() const;
	int getAutoDelaySpeed() const;


	/*
		@setters?
	*/
	void setAutoMode(bool mode);
	void setTextwindowTrans(int amnt);
	void setMessageSpeed(int speed);
	void setAutoDelaySpeed(int speed);

private:
	bool AutoMode;
	float DialogueBoxOpacity;
	int DialogueSpeed;
	int AutoDelaySpeed;


	/*
		@TODO
	*/
	//bool ContinueVoicePlaybackOnLine;
	//bool VoiceVolume;
	//bool ReadSkip;
	//bool AllSkip;

	bool nChanged;
};



#endif