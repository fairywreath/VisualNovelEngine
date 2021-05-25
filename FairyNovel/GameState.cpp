#include "GameState.hpp"
#include "Logger.hpp"
#include "Command.hpp"


#include <sfml/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(StateStack& stack, Context context) :
	State(stack, context),
	nCommandManager(*context.commandManager),
	nEngine(context),
	nConfigBtn(context, "CONFIG"),
	nBacklogBtn(context, "BACKLOG")
{
	nBackgroundSprite.setTexture(context.textures->get("MMBG"));

	context.configManager->applySettings(nEngine);

	std::cout << "COMMAND SIZE: " << nCommandManager.getCommands().size() << std::endl;

	nCommandManager.setEngine(nEngine);

	setButton(nConfigBtn);
	nConfigBtn.setPosition(800.f, ButtonsY);
	nConfigBtn.setCallback([this]() {
		requestStackPush(States::ID::Config);
		});

	setButton(nBacklogBtn);
	nBacklogBtn.setPosition(600.f, ButtonsY);
	nBacklogBtn.setCallback([this]() {
		requestStackPush(States::ID::Backlog);
		});
}

GameState::~GameState()
{
	/*
		@engine is scoped inside the game state, release it
	*/
	nCommandManager.releaseEngine();
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(nEngine);

	for (const auto& cmp : nComponents) window.draw(*cmp);

}

bool GameState::update(sf::Time dt)
{
	nEngine.update(dt);
	nCommandManager.update(dt);
	for (const auto& cmp : nComponents) cmp->update(dt);


	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	for (const auto& cmp : nComponents) cmp->handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		/*
			@maybe need to safeguard states, dont push same state twice
			or have two same states at the top of the stack
		*/
		requestStackPush(States::ID::Config);
		return false;
	}

	nEngine.handleEvent(event);

	/*
		@return true for cascading events between states
	*/
	return false;
}

void GameState::refresh()
{
	getContext().configManager->applySettings(nEngine);
}

void GameState::setButton(GUI::TextButton& btn)
{
	btn.setFont(getContext().fonts->get("aria"));
	btn.setSize(20);
	packComponent(&btn);
}

void GameState::packComponent(GUI::Component* cmp)
{
	nComponents.push_back(cmp);
}
