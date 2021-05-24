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

	void setupDefault();


private:
	/*
		@setup default
	*/
	static constexpr auto DefAutoMode = false;
	static constexpr auto DefTWindowTrans = 60.f;
	static constexpr auto DefDialSpeed = 5;
	static constexpr auto DefDelaySpeed = 1;

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
};



#endif