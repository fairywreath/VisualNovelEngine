#ifndef CONFIGBUTTON_HPP
#define CONFIGBUTTON_CPP

#include "Button.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

/*
	@button to set percetage/amount
*/
namespace GUI
{

class ConfigButton : public Button
{

public:
	explicit ConfigButton(State::Context context);
	~ConfigButton() override = default;
	
	void handleEvent(const sf::Event& event) override;

	float getAmount() const;

	/*
		@set initial amount
	*/
	void setAmount(int amount);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateApperance(ButtonState state) override;

	bool checkMouseLocation() const;

	void initializeRectangles();
	void updateColors(bool hover = false);

	void updateAppearannceOnClick();

private:
	static constexpr unsigned NumRects = 10;
	static constexpr float RectHeight = 25;
	static constexpr float RectWidth = 13;
	static constexpr float RectDist = 14;

	const sf::FloatRect ButtonBounds;

	const sf::Color FilledColor;
	const sf::Color HoverColor;
	const sf::Color NormalColor;
	
	const sf::RenderWindow& nWindow;

	std::vector<sf::RectangleShape> nRectangles;
	int nAmount;
};

}



#endif