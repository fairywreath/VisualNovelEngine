#ifndef CONFIGLABEL_HPP
#define CONFIGLABEL_HPP

#include "Label.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

/*
	@label for settings screen
*/

namespace GUI
{


class ConfigLabel : public Label
{
public:
	ConfigLabel(const std::string& text, const sf::Font& font);
	~ConfigLabel() override = default;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static constexpr auto RectLength = 16.f;
	static constexpr auto RectDist = 16;

	sf::RectangleShape nRect;

};


}

#endif