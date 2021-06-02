#ifndef SAVESTATE_HPP
#define SAVESTATE_HPP

#include "State.hpp"
#include "TextButton.hpp"
#include "Label.hpp"
#include "SavePanel.hpp"
#include "Components.hpp"

#include <SFML/Graphics/Sprite.hpp>

class SaveState : public State
{
public:
	SaveState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

	void setUpdateState(UpdateState state) override;

private:
	void packComponent(GUI::Component* cmpt);

private:
	struct SerializeSavedFormat
	{

	};


private:
	static constexpr auto TitleLabelX = 1200.f;
	static constexpr auto TitleLabelY = 680.f;
	static constexpr auto InfoLabelX = 630.f;

	GUI::Label nSectionLabel;
	GUI::Label nInfoLabel;
	GUI::TextButton nExitBtn;

	sf::Sprite nBackground;
	FadableSprite nFadableBg;

	std::vector<GUI::Component*> nComponents;

};



#endif