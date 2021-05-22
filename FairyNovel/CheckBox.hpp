#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "State.hpp"
#include "Component.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>


namespace GUI
{

class CheckBox : public Component
{

public:
	explicit CheckBox(State::Context context);
	~CheckBox() override = default;

	void handleEvent(const sf::Event& event) override;

	bool isSelectable() const override;

	void activate() override;

	bool getStatus() const;

private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	bool checkMouseLocation() const;

private:
	static constexpr float BoxWidth = 22;
	static constexpr float BoxHeight = 22;

	static constexpr float OutlineThickness = 2;
	const sf::Color Color;

	sf::RenderWindow& nWindow;

	sf::RectangleShape nRect;
	sf::Sprite nSprite;

	bool nChecked;

};

}

#endif