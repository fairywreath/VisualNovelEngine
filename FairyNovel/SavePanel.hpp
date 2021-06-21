#ifndef SAVEPANEL_HPP
#define SAVEPANEL_HPP

#include "Components.hpp"
#include "Button.hpp"
#include "State.hpp"
#include "Label.hpp"

#include <SFML\Graphics\RectangleShape.hpp>

namespace GUI
{

class SavePanel : public Button
{
public:
	SavePanel(State::Context context);

	~SavePanel() override = default;

	void intialize(State::Context context);

	void handleEvent(const sf::Event & event) override;
	void update(sf::Time dt) override;
	void fade(float time, int targetAlpha, int startAlpha) override;
	
	void setNumber(int num);
	int getNumber() const;
	
	void setSprite(const sf::Texture& texture);

	void setChapter(const std::string& str);
	void setDate(const std::string& str);
	void setDialogue(const std::string& str);

	void setOriginLeft();
	void setOriginRight();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateApperance(ButtonState state) override;

	bool checkMouseLocation() const;

	void setLabel(GUI::Label& label);

private:
	sf::RenderWindow& nWindow;

	sf::RectangleShape nOuterRect;
	FadableRectShape nFadableOuterRect;

	sf::RectangleShape nDialogueBox;
	FadableRectShape nFadableDB;

	GUI::Label nChapterTitleLabel;
	GUI::Label nDateTitleLabel;

	GUI::Label nNumberLabel;
	GUI::Label nChapterLabel;
	GUI::Label nDateLabel;
	GUI::Label nDialogueLabel;

	sf::Sprite nSprite;
	FadableSprite nFadableSrpite;

	int nNumber;

	std::vector<Component*> nComponents;
};

}

#endif