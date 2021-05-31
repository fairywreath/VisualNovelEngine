#ifndef CONFIGSTATE_HPP
#define CONFIGSTATE_HPP

#include "State.hpp"
#include "Label.hpp"
#include "ConfigLabel.hpp"
#include "ConfigButton.hpp"
#include "CheckBox.hpp"
#include "Container.hpp"
#include "TextButton.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

class ConfigState : public State
{
public:
	ConfigState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

	void setToRemovalAnimation() override;

private:
	/*
		@GUI component modifications
	*/
	void setNormalLabel(GUI::Label& label);

	/*
		@add to array
	*/
	void packComponent(GUI::Component* cmp);

	/*
		@refresh config appearances based on current settings, after setup default for eg. :)
	*/
	void refreshUI();

private:
	static constexpr auto ConfigLabelX = 210.f;

	static constexpr auto ConfigButton1X = 500.f;
	static constexpr auto ConfigButton2X = 880.f;

	static constexpr auto Label1X = 400.f;
	static constexpr auto Label2X = 730.f;

	static constexpr auto Row1Y = 80.f;
	static constexpr auto RowDist = 60.f;

	static constexpr auto TitleLabelX = 1200.f;
	static constexpr auto TitleLabelY = 680.f;


	std::vector<GUI::Component*> nComponents;

	/*
		@title label
	*/
	GUI::Label nSectionLabel;

	/*
		@normal labels
	*/
	GUI::Label nBgmLbl;
	GUI::Label nSeLbl;
	GUI::Label nMsgSpeedLbl;
	GUI::Label nAutoSpeedLbl;
	GUI::Label nTWindowTransLbl;
	GUI::Label nAutoModeLbl;


	/*
		@config buttons
	*/
	GUI::ConfigButton nBgmButton;
	GUI::ConfigButton nSeButton;
	GUI::ConfigButton nMsgSpeedButton;
	GUI::ConfigButton nAutoSpeedButton;
	GUI::ConfigButton nTWindowTransButton;

	/*
		@config labels
	*/
	GUI::ConfigLabel nSoundLabel;
	GUI::ConfigLabel nMessageLabel;
	GUI::ConfigLabel nVoiceLabel;
	GUI::ConfigLabel nEffectLabel;
	GUI::ConfigLabel nScreenLabel;
	GUI::ConfigLabel nEtcLabel;

	
	/*
		@checkboxes
	*/
	GUI::CheckBox nAutoModeCB;

	/*
		@textbuttons
	*/
	GUI::TextButton nExitButton;		// pops the config state
	GUI::TextButton nSetupDefaultButton;

	/*
		@bg
	*/
	sf::RectangleShape nBackground;
	sf::Sprite nSprite;
};


#endif