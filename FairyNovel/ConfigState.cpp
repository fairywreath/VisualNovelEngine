#include "ConfigState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

ConfigState::ConfigState(StateStack& stack, Context context) :
	State(stack, context),
	/*
		@section label
	*/
	nSectionLabel("CONFIG", context.fonts->get("sinkins")),
	/*
		@bg
	*/
	nBackground(context.textures->get("BG2")),
	/*
		@labels
	*/
	nBgmLbl("bgm volume", context.fonts->get("ttcommons")),
	nSeLbl("se volume", context.fonts->get("ttcommons")),
	nMsgSpeedLbl("message speed", context.fonts->get("ttcommons")),
	nAutoSpeedLbl("auto message speed", context.fonts->get("ttcommons")),
	nTWindowTransLbl("text window transparency", context.fonts->get("ttcommons")),
	nAutoModeLbl("auto read", context.fonts->get("ttcommons")),
	/*
		@config buttons
	*/
	nBgmButton(context),
	nSeButton(context),
	nMsgSpeedButton(context),
	nAutoSpeedButton(context),
	nTWindowTransButton(context),
	/*
		@config labels
	*/
	nSoundLabel("SOUND", context.fonts->get("huxleyv")),
	nMessageLabel("MESSAGE", context.fonts->get("huxleyv")),
	nVoiceLabel("VOICE", context.fonts->get("huxleyv")),
	nEffectLabel("EFFECT", context.fonts->get("huxleyv")),
	nScreenLabel("SCREEN", context.fonts->get("huxleyv")),
	nEtcLabel("Etc", context.fonts->get("huxleyv")),
	/*
		 @checkboxes
	*/
	nAutoModeCB(context)
{
	/*
		@title label
	*/
	nSectionLabel.setSize(85);
	nSectionLabel.setColor(sf::Color(249, 169, 178));
	nSectionLabel.setPosition(50.f, 580.f);

	nSoundLabel.setPosition(700.f, 500.f);

	nBgmButton.setPosition(200.f, 400.f);
	nBgmButton.setAmount((int)std::ceil((getContext().musicPlayer->getVolume() / 10.f)));
	nBgmButton.setCallback([this]() {
		getContext().musicPlayer->setVolume(nBgmButton.getAmount() * 10);
		});


	nAutoModeCB.setPosition(100.f, 400.f);
	auto callback = [this]() {
		if (nAutoModeCB.getStatus())
		{
			requestStackPop();;
			requestStackPush(States::ID::Game);
		}
	};
	nAutoModeCB.setCallback(callback);

	context.musicPlayer->play("mainmenu");
}


void ConfigState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	// window.draw(nBackground);
	window.draw(nSectionLabel);
	window.draw(nBgmButton);
	// std::cout << nAutoModeCB.getPosition().x << " " << nAutoModeCB.getPosition().y << std::endl;
	window.draw(nAutoModeCB);
	window.draw(nSoundLabel);
}


bool ConfigState::update(sf::Time dt)
{
	return false;
}


bool ConfigState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
	{
	//	requestStackPop();;
	//	requestStackPush(States::ID::Game);
	}

	nBgmButton.handleEvent(event);
	nAutoModeCB.handleEvent(event);

	return false;
}
