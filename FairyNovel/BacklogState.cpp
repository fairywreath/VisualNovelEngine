#include "BacklogState.hpp"
#include "Utility.hpp"

#include <iostream>

BacklogState::BacklogState(StateStack& stack, Context context) :
	State(stack, context),
	nDisplayCommands(context.commandManager->getBacklogCommands()),
	nBacklogs(Count),
	nBackground(static_cast<sf::Vector2f>(context.window->getSize())),
	nSprite(context.textures->get("EteFlowers")),
	nSectionLabel("BACKLOG", context.fonts->get("sinkins")),
	nFadableBg(nBackground),
	nFadableSprite(nSprite),
	nExitButton(context, "EXIT")
{
	/*
		@setup background
	*/
	nBackground.setFillColor(sf::Color::White);
	nBackground.setPosition(0, 0);
	nFadableBg.setObjectColor(sf::Color::White);
	nSprite.setPosition(880, 20);
	// context.musicPlayer->play("mainmenu");

	/*
		@setup title lable
	*/
	nSectionLabel.setSize(100);
	nSectionLabel.setColor(sf::Color(249, 169, 178));
	nSectionLabel.setOriginRight();
	nSectionLabel.setPosition(TitleLabelX, TitleLabelY);
	packComponent(&nSectionLabel);

	nExitButton.setFont(context.fonts->get("huxleyv"));
	nExitButton.setSize(55);
	nExitButton.setPosition(80.f, TitleLabelY);
	nExitButton.setCallback([this]() {
		requestStackPop();
		});
	packComponent(&nExitButton);

	nIP = nDisplayCommands.crbegin();
	
	for (int i = 0; i < Count; i++)
	{
		nBacklogs[i].setFont(context.fonts->get("overlock"));
		nBacklogs[i].setSize(FontSize);
		nBacklogs[i].setPosition(PanelX, PanelY + ((float)Count - (float)(i * PanelDist)));

		if (nIP != nDisplayCommands.crend())
		{
			setBacklogText(**nIP, nBacklogs[i]);
			nIP++;
		}

		packComponent(&nBacklogs[i]);
	}

	for (auto& bl : nBacklogs) packComponent(&bl);

	/*
		@intro fade animation
	*/
	for (const auto& cmp : nComponents)
	{
		cmp->fade(FadeTime, 255, 0);
	}

	nFadableBg.fade(FadeTime, 255, 0);
	nFadableSprite.fade(FadeTime, 255, 0);
}

BacklogState::~BacklogState()
{
}

void BacklogState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(nBackground);
	window.draw(nSprite);

	for (const auto& cmp : nComponents) window.draw(*cmp);
}

bool BacklogState::update(sf::Time dt)
{
	for (const auto& cmp : nComponents) cmp->update(dt);
	nFadableBg.update(dt);
	nFadableSprite.update(dt);

	return false;
}

void BacklogState::updateBacklog(int delta)
{
	/*
		@assume delta is positive, move UP
		@for now just set one by one
		@nIP is at the top, ahead of curr by 1, so use 1 for loop below
	*/
	if (delta > 0)
	{
		auto oldIP = nIP;
		while (delta > 0 && nIP != nDisplayCommands.crend())
		{
			nIP++;
			delta--;
		}
		if (oldIP == nIP) return;		// nothing to be done, already at the top

		/*
			@set three from the top
		*/
		auto runner = nIP;
		for (int i = Count - 1; i >= 0; i--)
		{
			if (runner == nDisplayCommands.crbegin()) break;
			runner--;
			setBacklogText(**runner, nBacklogs[i]);
		}
	}
	else if (delta < 0)				// need back pointer for this?
	{
		/*
			@get bottom text
		*/
		auto runner = nIP;
		for (int i = 0; i < Count && runner != nDisplayCommands.crbegin(); i++)
		{
			runner--;
		}
		// current runner head is current pointer for child
		while (delta < 0 && runner != nDisplayCommands.crbegin())
		{
			runner--;
			delta++;
		}
		/*
			@set from bottom
		*/
		for (int i = 0; i < Count; i++)
		{
			if (runner == nDisplayCommands.crend()) break;
			setBacklogText(**runner, nBacklogs[i]);
			runner++;
		}
		nIP = runner;
	}
	else
	{
		// empty
	}
}

void BacklogState::setUpdateState(UpdateState state)
{
	State::setUpdateState(state);
	if (state == UpdateState::InRemovalAnimation)
	{
		for (const auto& cmp : nComponents)
		{
			cmp->fade(FadeTime, 0, 255);
		}

		nFadableBg.fade(FadeTime, 0, 255);
		nFadableSprite.fade(FadeTime, 0, 255);
	}
	else if (state == UpdateState::OnTop)
	{
		for (const auto& cmp : nComponents)
		{
			cmp->fade(FadeTime, 255, 0);
		}

		nFadableBg.fade(FadeTime, 255, 0);
		nFadableSprite.fade(FadeTime, 255, 0);
	}
	else
	{

	}
}

bool BacklogState::handleEvent(const sf::Event& event)
{
	for (const auto& cmp : nComponents) cmp->handleEvent(event);

	if (event.type == sf::Event::MouseWheelMoved)
	{
		updateBacklog(event.mouseWheel.delta);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
	{
		updateBacklog(1);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
	{
		updateBacklog(-1);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}



	return false;
}

void BacklogState::packComponent(GUI::Component* cmp)
{
	nComponents.push_back(cmp);
}

/*
	@specifically for display text commands
*/
void BacklogState::setBacklogText(Command& command, GUI::BacklogPanel& backlog)
{
	backlog.setIdentifier(command.getIdentifier());
	backlog.setText(command.getArgumentString());
}

