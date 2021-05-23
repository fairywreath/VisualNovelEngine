#ifndef CONFIGSTATE_HPP
#define CONFIGSTATE_HPP

#include "State.hpp"
#include "Label.hpp"
#include "ConfigLabel.hpp"
#include "ConfigButton.hpp"
#include "CheckBox.hpp"

#include <SFML/Graphics/Sprite.hpp>

class ConfigState : public State
{
public:
	ConfigState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;


private:
	/*
		@GUI component modifications
	*/
	


private:
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
		@bg
	*/
	sf::Sprite nBackground;

};


#endif