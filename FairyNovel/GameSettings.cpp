#include "GameSettings.hpp"

GameSettings::GameSettings() :
	nChanged(false)
{
}

void GameSettings::sendEvents()
{
}

bool GameSettings::isChanged() const
{
	return nChanged;
}
