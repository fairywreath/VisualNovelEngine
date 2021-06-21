#include "GameState.hpp"
#include "Logger.hpp"
#include "Command.hpp"

#include <sfml/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(StateStack& stack, Context context) :
	State(stack, context),
	nCommandManager(*context.commandManager),
	nEngine(context, *this),
	nConfigBtn(context, "CONFIG"),
	nBacklogBtn(context, "BACKLOG"),
	nAutoModeBtn(context, "AUTO"),
	nExitBtn(context, "EXIT"),
	nInDecision(false)
{
	context.configManager->applySettings(nEngine);

	std::cout << "COMMAND SIZE: " << nCommandManager.getCommands().size() << std::endl;

	nCommandManager.setEngine(nEngine);

	setButton(nExitBtn);
	nExitBtn.setPosition(ButtonsStartY, ButtonsY);
	nExitBtn.setCallback([this]() {
		requestStackPop();
		requestStackPushAfter(States::ID::MainMenu, 1.f);
		});

	setButton(nConfigBtn);
	nConfigBtn.setPosition(nExitBtn.getBoundingRect().left - nConfigBtn.getBoundingRect().width -
		ButtonsDist, ButtonsY);
	nConfigBtn.setCallback([this]() {
		requestStackPush(States::ID::Config);
		});

	setButton(nBacklogBtn);
	nBacklogBtn.setPosition(nConfigBtn.getBoundingRect().left - nBacklogBtn.getBoundingRect().width - 
		ButtonsDist, ButtonsY);
	nBacklogBtn.setCallback([this]() {
		requestStackPush(States::ID::Backlog);
		});

	setButton(nAutoModeBtn);
	nAutoModeBtn.setPosition(nBacklogBtn.getBoundingRect().left - nAutoModeBtn.getBoundingRect().width -
		ButtonsDist, ButtonsY);
	nAutoModeBtn.setCallback([&engine = nEngine]() {
		engine.setAuto(!engine.getAuto());
		});

	unsigned NumComponents = 10;		// use 10 for now
	nComponents.reserve(NumComponents);
	nDecisionBtns.reserve(NumComponents / 2);

	setUpdateState(State::UpdateState::OnTop);
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

	if (!nInDecision && (nDecisionBtns.size() != 0) && !nDecisionBtns.back()->inAnimation())
	{
		clearDecisions();
	}

	getContext().musicPlayer->update(dt);

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

	if (!nInDecision)
		nEngine.handleEvent(event);

	/*
		@return true for cascading events between states
	*/
	return false;
}

void GameState::setUpdateState(UpdateState state)
{
	State::setUpdateState(state);

	if (state == UpdateState::OnTop)
	{
		getContext().configManager->applySettings(nEngine);
		nCommandManager.resume();
		nEngine.fadeInScreen(1.f);
		getContext().musicPlayer->fadeIn(1.f);
	}
	else if (state == UpdateState::InRemovalAnimation)
	{
		for (auto& cmp : nComponents) cmp->fade(1.f, 0, 255);

		nCommandManager.stop();
		nEngine.stopAllAnimations();
		nEngine.clearScreen(1.f);
		getContext().musicPlayer->fadeOut(1.f);
	}
	else
	{

	}
}

void GameState::setButton(GUI::TextButton& btn)
{
	btn.setFont(getContext().fonts->get("aria"));
	btn.setSize(25);
	packComponent(&btn);
}

void GameState::packComponent(GUI::Component* cmp)
{
	nComponents.push_back(cmp);
}

void GameState::setDecisionState()
{
	// reset if buttons currently exit to prevent race condition(very unlikely in actual scripting though)
	if (!nInDecision && (nDecisionBtns.size() != 0))
	{
		clearDecisions();
	}
	
	nInDecision = true;
}

void GameState::addDecisionButton(const std::string& text, const std::string& targetLabel)
{
	auto button = std::make_unique<GUI::TextButton>(getContext(), text);
	nComponents.push_back(button.get());
	button->setPosition((float)DecisionX, (float)(DecisionStartY + (nDecisionBtns.size() * DecisionDist)));
	button->fade(0.6f, 255, 0);

	button->setCallback([this, targetLabel]() {
		getContext().commandManager->jumpCommandLabel(targetLabel);
		for (auto& btn : nDecisionBtns)
		{
			btn->fade(0.6f, 0, 255);
		}
		nInDecision = false;		
		});

	nDecisionBtns.push_back(std::move(button));
}

void GameState::clearDecisions()
{
	/*
		@decision is always at the end of the components vector
	*/
	for (int i = 0; i < nDecisionBtns.size(); i++)
	{
		nComponents.pop_back();
	}
	nDecisionBtns.clear();
}
