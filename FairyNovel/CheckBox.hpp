#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "State.hpp"
#include "Button.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

/*
	@acts like a button
*/
#include <functional>

namespace GUI
{

class CheckBox : public Button
{

public:
	explicit CheckBox(State::Context context);
	~CheckBox() override = default;

	void handleEvent(const sf::Event& event) override;

	bool getStatus() const;

private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	bool checkMouseLocation() const;

	void updateApperance(ButtonState state) override;

private:
	static constexpr float BoxWidth = 22;
	static constexpr float BoxHeight = 22;

	static constexpr float OutlineThickness = 2.5;
	const sf::Color OutlineColor;
	const sf::Color HoverColor;

	sf::RenderWindow& nWindow;

	sf::RectangleShape nRect;
	sf::Sprite nSprite;

	bool nChecked;

};

}

#endif