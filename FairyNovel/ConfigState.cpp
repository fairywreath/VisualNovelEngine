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
	packComponent(&nSectionLabel);

	/*
		@normal labels
	*/
	setNormalLabel(nBgmLbl);
	nBgmLbl.setPosition(Label1X, Row1Y);
	packComponent(&nBgmLbl);

	setNormalLabel(nSeLbl);
	nSeLbl.setPosition(Label2X, Row1Y);
	packComponent(&nSeLbl);

	setNormalLabel(nSeLbl);
	setNormalLabel(nMsgSpeedLbl);
	setNormalLabel(nAutoSpeedLbl);
	setNormalLabel(nTWindowTransLbl);
	setNormalLabel(nAutoModeLbl);



	/*
		@config buttons
	*/
	nBgmButton.setPosition(ConfigButton1X, Row1Y);
	nBgmButton.setAmount((int)std::ceil((getContext().musicPlayer->getVolume() / 10.f)));
	nBgmButton.setCallback([this]() {
		getContext().musicPlayer->setVolume(nBgmButton.getAmount() * 10);
		});
	packComponent(&nBgmButton);

	nSeButton.setPosition(ConfigButton2X, Row1Y);
	nSeButton.setAmount((int)std::ceil((getContext().soundPlayer->getVolume() / 10.f)));
	nSeButton.setCallback([this]() {
		getContext().soundPlayer->setVolume(nSeButton.getAmount() * 10);
		});
	packComponent(&nSeButton);


	/*
		@config labels, dist between configlabel and normaallabel/config button = 40
	*/
	nSoundLabel.setPosition(ConfigLabelX, Row1Y);
	packComponent(&nSoundLabel);

	nMessageLabel.setPosition(ConfigLabelX, Row1Y + RowDist);
	packComponent(&nMessageLabel);


	nAutoModeCB.setPosition(100.f, 400.f);
	auto callback = [this]() {
		if (nAutoModeCB.getStatus())
		{
			requestStackPop();;
			requestStackPush(States::ID::Game);
		}
	};
	nAutoModeCB.setCallback(callback);
	packComponent(&nAutoModeCB);

	context.musicPlayer->play("mainmenu");
}


void ConfigState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	// window.draw(nBackground);


	for (const auto& cmp : nComponents) window.draw(*cmp);
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

	for (const auto& cmp : nComponents) cmp->handleEvent(event);

	return false;
}

void ConfigState::setNormalLabel(GUI::Label& label)
{
	label.setSize(22);
	label.setColor(sf::Color(249, 169, 178));
	label.centerOriginX();
}

void ConfigState::packComponent(GUI::Component* cmp)
{
	nComponents.push_back(cmp);
}
