#ifndef TEXTBUTTON_HPP
#define TEXTBUTTON_HPP

#include "Button.hpp"

#include "Components.hpp"
#include "Animatable.hpp"
#include "Movable.hpp"

namespace GUI
{

class TextButton : public Button
{
public:
	TextButton(State::Context context, const std::string& text);
	~TextButton() override = default;

	void handleEvent(const sf::Event & event) override;

	void setText(const std::string & text);
	void setFont(const sf::Font& font);
	void setSize(int size);

	void refreshOrigin();

	void update(sf::Time dt) override;

	void fade(float time, int targetAlpha, int startAlpha) override;
	void move(float time, const sf::Vector2f& dest, const sf::Vector2f& source) override;

	void setBold();
	void setHoverColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& color);
	void setFilledColor(const sf::Color& color);
	void setNormalColor(const sf::Color& color);
	void setOutlineThicknes(float amount);
	void setHoverOutlineDist(float amount);

	sf::FloatRect getBoundingRect() const override;

private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void updateApperance(ButtonState state) override;

	bool checkMouseLocation() const;

private:
	AnimatableText nAnimeText;
	sf::Text nText;

	Movable nMover;

	sf::Color FilledColor;
	sf::Color HoverColor;
	sf::Color NormalColor;

	sf::Color OutlineHoverColor;

	sf::RenderWindow& nWindow;

	float nBaseOutlineThickness;
	float nOutlineDist;
};

}



#endif