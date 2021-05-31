#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Achievement.hpp"

#include <unordered_map>
#include <memory>

class Player
{
public:
	using AchPtr = std::unique_ptr<Achievement>;

	Player();

	void addPoints(const std::string& route, int amount);
	int getPoints(const std::string& route) const;

	bool unlock(const std::string& achievement);		// return false if achievement doesnt exist
	void unlockIfPointsSuffice(int points, const std::string& route, const std::string& achievement);

	bool isUnlocked(const std::string& achivement) const;

	void addRoute(const std::string& name);
	void addAchievement(const std::string& id, const sf::Texture& locked, const sf::Texture& unlocked);

private:
	std::unordered_map<std::string, int> nRoutesMap;
	std::unordered_map<std::string, AchPtr> nAchievements;

};




#endif