#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

#include <utility>

namespace Util
{
	template <typename Type>
	std::string toString(const Type& value);

	std::string toString(sf::Keyboard::Key key);

	sf::String wrapText(sf::String string, unsigned width, const sf::Font& font, unsigned characterSize,
		unsigned extraLen, bool bold = false);

	std::vector<std::string> split(const std::string& str, char delimiter);
	std::string trim(const std::string& str);
	bool checkEnds(std::string& str, char lhs, char rhs);
	std::string trimEnds(const std::string& str);

	std::vector<std::string> splitAndTrim(const std::string& str, char delimiter);

	std::vector<std::pair<std::string, std::string>> getCommandArgumentPairs(const std::string& str);


	// vector operations
	float length(sf::Vector2f vector);			// get modulus
	sf::Vector2f unitVector(sf::Vector2f vector);

	bool isNumber(const std::string& str);

	template <typename T>
	void centerOrigin(T& object);
}


#include "Utility.inl"
#endif