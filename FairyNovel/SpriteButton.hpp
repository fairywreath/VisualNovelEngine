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
		~SpriteButton() override = default;

		void handleEvent(const sf::Event& event) override;

		void setText(const std::string& text);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void updateApperance(ButtonState state) override;

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