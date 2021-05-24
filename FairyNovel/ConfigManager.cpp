#include "ConfigManager.hpp"
#include "Engine.hpp"

#include <iostream>

ConfigManager::ConfigManager() :
	AutoMode(DefAutoMode),
	DialogueBoxOpacity(DefTWindowTrans),
	DialogueSpeed(DefDialSpeed),
	AutoDelaySpeed(DefDelaySpeed)
{
}

void ConfigManager::setupDefault()
{
	AutoMode = DefAutoMode;
	DialogueBoxOpacity = DefTWindowTrans;
	DialogueSpeed = DefDialSpeed;
	AutoDelaySpeed = DefDelaySpeed;
}


void ConfigManager::applySettings(Engine& engine)
{
	std::cout << "TRANSPARENCY: " << DialogueBoxOpacity << std::endl;
	engine.setDialogueBoxOpacityPercent(DialogueBoxOpacity);

	std::cout << "AUTO: " << AutoMode << std::endl;
	engine.setAuto(AutoMode);

	std::cout << "DIAL SPEED: " << DialogueSpeed << std::endl;
	engine.setDialogueSpeed(DialogueSpeed);
	
	std::cout << "AUTO SPEED: " << AutoDelaySpeed << std::endl;
	engine.setAutoSpeed(AutoDelaySpeed);

	std::cout << "apply settings finished\n";
}

bool ConfigManager::getAutoMode() const
{
	return AutoMode;
}

float ConfigManager::getTextWindowTrans() const
{
	return DialogueBoxOpacity;		// percent
}

int ConfigManager::getMessageSpeed() const
{
	return DialogueSpeed;
}

int ConfigManager::getAutoDelaySpeed() const
{
	return AutoDelaySpeed;
}

void ConfigManager::setAutoMode(bool mode)
{
	AutoMode = mode;
}

void ConfigManager::setTextwindowTrans(int amnt)
{
	DialogueBoxOpacity = static_cast<float>(amnt);
}

void ConfigManager::setMessageSpeed(int speed)
{
	DialogueSpeed = speed;
}

void ConfigManager::setAutoDelaySpeed(int speed)
{
	AutoDelaySpeed = speed;
}




