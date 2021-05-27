#include "Player.hpp"

#include "Logger.hpp"

Player::Player() :
	nRoutesMap(),
	nAchievements(),
	nUnlocked()
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
	nAchievements.push_back(std::make_unique<Achievement>(id, locked, unlocked));
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

void Player::unlock(const std::string& achievement)
{
	auto found = std::find_if(nAchievements.begin(), nAchievements.end(), 
		[&](const AchPtr& ac) {
			return ac->getIdentifier() == achievement;
		});

	if (found != nAchievements.end())
	{
		(*found)->unlock();
	}
	else
	{
		// log
	}
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

const std::vector<Achievement*>& Player::getUnlocked() const
{
	return nUnlocked;
}

const std::vector<Player::AchPtr>& Player::getAchievments() const
{
	return nAchievements;
}




