#ifndef SPRITEBUTTON_HPP
#define SPRITEBUTTON_HPP

/*
	sprite button through mouse
*/

#include "Button.hpp"

namespace GUI
{
	class SpriteButton : public Button
	{
	public:
		explicit SpriteButton(State::Context context);
		virtual void handleEvent(const sf::Event& event);

		void setText(const std::string& text);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void updateApperance(ButtonState state);

		bool checkMouseLocation() const;		// realtime

	private:
		const sf::RenderWindow& nWindow;

		const sf::Texture& nNormalTexture;
		const sf::Texture& nHoverTexture;
		const sf::Texture& nPressedTexture;

		sf::Sprite nSprite;
		sf::Text nText;

	};
}


#endif