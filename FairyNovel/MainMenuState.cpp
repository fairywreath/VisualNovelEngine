#include "MainMenuState.hpp"

MainMenuState::MainMenuState(StateStack& stack, Context context) :
	State(stack, context),
	nBackground("BG", context.textures->get("MainMenuBG")),
	nTitle("Title", context.textures->get("MMLogo")),
	nStartBtn(context, "START"),
	nLoadgBtn(context, "LOAD"),
	nConfigBtn(context, "CONFIG"),
	nGalleryBtn(context, "GALLERY"),		// or achievements
	nExitBtn(context, "EXIT"),
	nBgDone(false),
	nTitleDone(false),
	nFadableRect(nGUIWindow),
	nRectMover(&nGUIWindow),
	nAnimationTime(sf::Time::Zero)
{
	initialize();

	//context.characterManager->playVoice("", "Media/VoiceLines/suoh_intro.ogg");
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::initialize()
{
	nBackground.fade(2.5, 255, 0);
	getContext().musicPlayer->play("AutomneMM");

	nBackground.setPosition(0.f, 0.f);

	/*
		@entity origin at top left(default)
		@entity origin not cetered, need to manually adjust to center it
	*/
	sf::Vector2u wSize = getContext().window->getSize();
	sf::FloatRect eBounds = nTitle.getBoundingRect();
	nTitle.setPosition((wSize.x / 2) - (eBounds.width / 2), (wSize.y / 2) - (eBounds.height / 2) + 60);
}

void MainMenuState::setupButtons()
{
	setButton(nStartBtn);
	setButton(nLoadgBtn);
	setButton(nConfigBtn);
	setButton(nGalleryBtn);
	setButton(nExitBtn);

	nStartBtn.setCallback([this]() {
		requestStackPop();
		requestStackPush(States::ID::Game);
		});

	nConfigBtn.setCallback([this]() {
	//	requestStackPop();
		requestStackPush(States::ID::Config);
		});

	nExitBtn.setCallback([this]() {
		requestStackPop();
		});

	for (int i = 0; i < ButtonCount; i++)
	{
		nComponents[i]->move(0.5, sf::Vector2f((float)ButtonsX, (float)(ButtonsStartY + (i * ButtonsDist))), 
			sf::Vector2f((float)(ButtonsX + 40), (float)(ButtonsStartY + (i * ButtonsDist))));
	}

	nGUIWindow.setSize(sf::Vector2f(ButtonsX - 40, 800));
	nGUIWindow.setOutlineColor(sf::Color(249, 169, 178));
	nGUIWindow.setFillColor(sf::Color(255, 255, 255, 125));
	nGUIWindow.setOutlineThickness(6);

	nFadableRect.setBothFillOutline(true);
	nFadableRect.setOutlineColor(sf::Color(249, 169, 178));
	nFadableRect.setObjectColor(sf::Color::White);

	nRectMover.move(0.5, sf::Vector2f(ButtonsX - 40, -10), sf::Vector2f(ButtonsX, -10));
}


void MainMenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(nBackground);

	if (nBgDone) window.draw(nTitle);

	if (nTitleDone)
	{
		window.draw(nFadableRect);
		for (const auto& cmp : nComponents) window.draw(*cmp);
	}
}

bool MainMenuState::update(sf::Time dt)
{
	/*
		@setup slideshow here
	*/
	if (!nBackground.inAnimation() && !nBgDone)
	{
		nBgDone = true;
		nTitle.fade(2, 255, 0);
	}
	if (!nTitle.inAnimation() && nBgDone && !nTitleDone)
	{
		nTitleDone = true;
		setupButtons();
	}

	nBackground.update(dt);
	if (nBgDone) nTitle.update(dt);

	if (nTitleDone)
	{
		for (const auto& cmp : nComponents) cmp->update(dt);
		nFadableRect.update(dt);
		nRectMover.update(dt);
	}

	return false;
}

bool MainMenuState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		/*
			@skipp all anims
		*/
		if (!nBgDone || !nTitleDone)
		{
			nBgDone = true;
			nTitleDone = true;
			nBackground.skipAnimation();
			nTitle.skipAnimation();
			setupButtons();
		}
	}

	if (nTitleDone)
	{
		for (const auto& cmp : nComponents) cmp->handleEvent(event);
	}

	return false;
}

void MainMenuState::setUpdateState(UpdateState state)
{
	State::setUpdateState(state);
	if (state == UpdateState::InRemovalAnimation)
	{
		for (const auto& cmp : nComponents)
		{
			cmp->fade(FadeTime, 0, 255);
		}

		nFadableRect.fade(FadeTime, 0, 125);
		nBackground.fade(FadeTime, 0, 255);
		nTitle.fade(FadeTime, 0, 255);
	}
	else if (state == UpdateState::OnTop)
	{
		for (const auto& cmp : nComponents)
		{
			cmp->fade(FadeTime, 255, 0);
		}

		nFadableRect.fade(FadeTime, 125, 0);
		nBackground.fade(FadeTime, 255, 0);
		nTitle.fade(FadeTime, 255, 0);
	}
	else
	{

	}
}

void MainMenuState::setButton(GUI::TextButton& btn)
{
	btn.setFont(getContext().fonts->get("veljovic"));
	//btn.setBold();
	btn.setSize(34);
	btn.setOutlineColor(sf::Color(249, 169, 178));
	btn.setOutlineThicknes(1.5);
	btn.setHoverOutlineDist(0);
	btn.setNormalColor(sf::Color(255, 255, 255));
	btn.setHoverColor(sf::Color(161, 100, 108));

	packComponent(&btn);
}

void MainMenuState::packComponent(GUI::Component* cmp)
{
	nComponents.push_back(cmp);
}



