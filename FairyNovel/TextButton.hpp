#ifndef TEXTBUTTON_HPP
#define TEXTBUTTON_HPP

#include "Button.hpp"

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

private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void updateApperance(ButtonState state) override;

	bool checkMouseLocation() const;

private:
	sf::Text nText;

	const sf::Color FilledColor;
	const sf::Color HoverColor;
	const sf::Color NormalColor;

	const sf::Color OutlineHoverColor;

	sf::RenderWindow& nWindow;
};

}



#endif