#include "Player.hpp"

#include "Logger.hpp"

Player::Player() :
	nRoutesMap(),
	nAchievements()
{
}

void Player::addRoute(const std::string& name)
{
	if (nRoutesMap.find(name) != nRoutesMap.end())
	{
		// log
		return;
	}

	nRoutesMap.insert(std::make_pair(name, 0));
}

void Player::addAchievement(const std::string& id, const sf::Texture& locked, const sf::Texture& unlocked)
{
	if (nAchievements.find(id) == nAchievements.end())
	{
		// log
		return;
	}

	nAchievements.insert(std::make_pair(id, 
		std::make_unique<Achievement>(id, locked, unlocked)));
}

void Player::addPoints(const std::string& route, int amount)
{
	if (nRoutesMap.find(route) == nRoutesMap.end())
	{
		// log
		return;
	}
	nRoutesMap.at(route) += amount;
}

int Player::getPoints(const std::string& route) const
{
	if (nRoutesMap.find(route) == nRoutesMap.end())
	{
		// log
		return INT_MAX;
	}

	return nRoutesMap.at(route);
}

bool Player::unlock(const std::string& achievement)
{
	if (nAchievements.find(achievement) == nAchievements.end())
	{
		// log
		return false;
	}

	nAchievements.at(achievement)->unlock();
	return true;
}

void Player::unlockIfPointsSuffice(int points, const std::string& route,  const std::string& achievement)
{
	if (nRoutesMap.find(route) == nRoutesMap.end())
	{
		// log
		return;
	}

	if (nRoutesMap.at(route) < points) return;

	unlock(achievement);
}

bool Player::isUnlocked(const std::string& achievement) const
{
	if (nAchievements.find(achievement) == nAchievements.end())
	{
		// log
		return false;
	}

	return !nAchievements.at(achievement)->isLocked();
}




