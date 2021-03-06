#ifndef LABEL_HPP
#define LABEL_HPP

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "Components.hpp"

#include <SFML/Graphics/Text.hpp>

/*
	@will add movement/animations later
*/

namespace GUI
{

class Label : public Component
{
public:
	Label();
	Label(const std::string& text, const sf::Font& font);
	~Label() override = default;

	/*
		@component member functions
	*/
	bool isSelectable() const override;
	void handleEvent(const sf::Event& event) override;

	/*
		@label functionalities
	*/
	void setText(const std::string& text);
	void setFont(const sf::Font& font);
	void setSize(unsigned int size);
	void setColor(const sf::Color& color);

	int getSize() const;

	void centerOriginX();
	void setOriginBottom();

	void setOriginLeft();
	void setOriginRight();
	void setOriginTop();

	void fade(float time, int targetAlpha, int startAlpha) override;
	void update(sf::Time dt) override;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Text nText;
	FadableText nFadableText;
};

}






#endif