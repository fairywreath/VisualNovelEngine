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
	nBackground(static_cast<sf::Vector2f>(context.window->getSize())),
	nSprite(context.textures->get("EteFlowers")),
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
	nAutoModeCB(context),
	/*
		@text buttons
	*/
	nExitButton(context, "EXIT"),
	nSetupDefaultButton(context, "SETUP DEFAULT")
{
	/*
		@title label
	*/
	nSectionLabel.setSize(100);
	nSectionLabel.setColor(sf::Color(249, 169, 178));
	nSectionLabel.setOriginRight();
	nSectionLabel.setPosition(TitleLabelX, TitleLabelY);
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

	setNormalLabel(nMsgSpeedLbl);
	nMsgSpeedLbl.setPosition(Label1X, Row1Y + RowDist);
	packComponent(&nMsgSpeedLbl);

	setNormalLabel(nAutoSpeedLbl);
	nAutoSpeedLbl.setPosition(Label2X, Row1Y + RowDist);
	packComponent(&nAutoSpeedLbl);

	setNormalLabel(nAutoModeLbl);
	nAutoModeLbl.setPosition(Label1X, Row1Y + (1.7 * RowDist));
	packComponent(&nAutoModeLbl);

	setNormalLabel(nTWindowTransLbl);
	nTWindowTransLbl.setPosition(Label1X, Row1Y + (5 * RowDist));
	packComponent(&nTWindowTransLbl);

	/*
		@config buttons
	*/
	nBgmButton.setPosition(ConfigButton1X, Row1Y);
	//nBgmButton.setAmount((int)std::ceil((getContext().musicPlayer->getVolume() / 10.f)));
	nBgmButton.setCallback([context, &nBgmButton = nBgmButton]() {
		context.musicPlayer->setVolume(static_cast<float>(nBgmButton.getAmount() * 10));
		});
	packComponent(&nBgmButton);

	nSeButton.setPosition(ConfigButton2X, Row1Y);
	//nSeButton.setAmount((int)std::ceil((getContext().soundPlayer->getVolume() / 10.f)));
	nSeButton.setCallback([context, &nSeButton = nSeButton]() {
		context.soundPlayer->setVolume(static_cast<float>(nSeButton.getAmount() * 10));
		});
	packComponent(&nSeButton);

	nMsgSpeedButton.setPosition(ConfigButton1X, Row1Y + RowDist);
	//nMsgSpeedButton.setAmount(context.configManager->getMessageSpeed());
	nMsgSpeedButton.setCallback([context, &nMsgSpeedButton = nMsgSpeedButton]() {
		context.configManager->setMessageSpeed(nMsgSpeedButton.getAmount());
		});
	packComponent(&nMsgSpeedButton);

	nAutoSpeedButton.setPosition(ConfigButton2X, Row1Y + RowDist);
	//nAutoSpeedButton.setAmount(context.configManager->getAutoDelaySpeed());
	nAutoSpeedButton.setCallback([context, &nAutoSpeedButton = nAutoSpeedButton]() {
		context.configManager->setAutoDelaySpeed(nAutoSpeedButton.getAmount());
		});
	packComponent(&nAutoSpeedButton);

	nTWindowTransButton.setPosition(ConfigButton2X - 200.f, Row1Y + (5 * RowDist));
	//nTWindowTransButton.setAmount(static_cast<int>(context.configManager->getTextWindowTrans() / 10.f));
	nTWindowTransButton.setCallback([context, &nTWindowTransButton = nTWindowTransButton]() {
		context.configManager->setTextwindowTrans(nTWindowTransButton.getAmount() * 10);
		// std::cout << "YEAHHHH " << nTWindowTransButton.getAmount() << std::endl;
		});
	packComponent(&nTWindowTransButton);

	/*
		@config labels, dist between configlabel and normaallabel/config button = 40
	*/
	nSoundLabel.setPosition(ConfigLabelX, Row1Y);
	packComponent(&nSoundLabel);

	nMessageLabel.setPosition(ConfigLabelX, Row1Y + RowDist);
	packComponent(&nMessageLabel);

	nVoiceLabel.setPosition(ConfigLabelX, Row1Y + (2.5 * RowDist));
	packComponent(&nVoiceLabel);

	nEffectLabel.setPosition(ConfigLabelX, Row1Y + (4 * RowDist));
	packComponent(&nEffectLabel);

	nScreenLabel.setPosition(ConfigLabelX, Row1Y + (5 * RowDist));
	packComponent(&nScreenLabel);

	nEtcLabel.setPosition(ConfigLabelX, Row1Y + (7 * RowDist));
	packComponent(&nEtcLabel);

	/*
		@checkboxes
	*/
	nAutoModeCB.setPosition(ConfigButton1X, Row1Y + (1.7 * RowDist));
	auto callback = [context, &nAutoModeCB = nAutoModeCB]() {				// capture by ref like this
		context.configManager->setAutoMode(nAutoModeCB.getStatus());
	};
	nAutoModeCB.setCallback(callback);
	packComponent(&nAutoModeCB);

	/*
		@text buttons
	*/
	nExitButton.setFont(context.fonts->get("huxleyv"));
	nExitButton.setSize(55);
	nExitButton.setPosition(80.f, TitleLabelY);
	nExitButton.setCallback([this]() {
		requestStackPop();
		});
	packComponent(&nExitButton);

	nSetupDefaultButton.setFont(context.fonts->get("huxleyv"));
	nSetupDefaultButton.setSize(55);
	nSetupDefaultButton.setPosition(170.f, TitleLabelY);
	nSetupDefaultButton.setCallback([this]() {
		getContext().musicPlayer->setupDefault();
		getContext().soundPlayer->setupDefault();
		getContext().configManager->setupDefault();
		refreshUI();
		});
	packComponent(&nSetupDefaultButton);

	refreshUI();

	nBackground.setFillColor(sf::Color::White);
	nBackground.setPosition(0, 0);
	nSprite.setPosition(880, 20);
//	context.musicPlayer->play("mainmenu");



	/*
		@misc animations
	*/
	nSetupDefaultButton.fade(0.6f, 255, 0);
	nAutoModeCB.fade(2.f, 255, 0);
	nAutoModeCB.setStatus(true);
	//nSetupDefaultButton.move(5, sf::Vector2f(170.f, TitleLabelY), sf::Vector2f(100, 100));
}

void ConfigState::refreshUI()
{

	nBgmButton.setAmount((int)std::ceil((getContext().musicPlayer->getVolume() / 10.f)));
	nSeButton.setAmount((int)std::ceil((getContext().soundPlayer->getVolume() / 10.f)));
	nMsgSpeedButton.setAmount(getContext().configManager->getMessageSpeed());
	nAutoSpeedButton.setAmount(getContext().configManager->getAutoDelaySpeed());
	nTWindowTransButton.setAmount(static_cast<int>
		(getContext().configManager->getTextWindowTrans() / 10.f));

	nAutoModeCB.setStatus(getContext().configManager->getAutoMode());
}


void ConfigState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(nBackground);
	window.draw(nSprite);

	for (const auto& cmp : nComponents) window.draw(*cmp);

}


bool ConfigState::update(sf::Time dt)
{
	for (const auto& cmp : nComponents) cmp->update(dt);

	return false;
}


bool ConfigState::handleEvent(const sf::Event& event)
{
	for (const auto& cmp : nComponents) cmp->handleEvent(event);

	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
	{
	//	requestStackPop();;
	//	requestStackPush(States::ID::Game);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	return false;			
}

void ConfigState::setNormalLabel(GUI::Label& label)
{
	label.setSize(19);
	label.setColor(sf::Color(249, 169, 178));
	label.centerOriginX();
}

void ConfigState::packComponent(GUI::Component* cmp)
{
	nComponents.push_back(cmp);
}


