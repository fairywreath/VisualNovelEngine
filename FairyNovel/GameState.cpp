#include "GameState.hpp"
#include "Logger.hpp"
#include <sfml/Graphics/RenderWindow.hpp>

#include <iostream>

GameState::GameState(StateStack& stack, Context context) :
	State(stack, context),
	nCommands(*context.commands),
	nIP(context.commands->cbegin()),
	nCommandLabels(*context.commandLabels),
	nEngine(context)
{
	nBackgroundSprite.setTexture(context.textures->get("MMBG"));
	context.musicPlayer->play("mainmenu");

	std::cout << "Command Label size: " << nCommandLabels.size();
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(nEngine);
}

bool GameState::update(sf::Time dt)
{
	// let engine update
	// if engine not int wait state
	nEngine.update(dt);

	if (!nEngine.shouldWait() && nIP != nCommands.cend())
	{
		if ((*nIP)->getType() == Command::Type::Label)
		{
			nIP++;		// skip label declarations, executing them also yeilds void() nothing
		}
		else if ((*nIP)->getType() == Command::Type::Jump)
		{
			if (nCommandLabels.find((*nIP)->getIdentifier()) == nCommandLabels.cend())
			{
				std::string msg = "Could not find script label " + (*nIP)->getIdentifier();
				LOGGER->Log("Command Jump error", msg);
			//	std::cout << msg << std::endl;
				nIP++;		// for now just go to next 
			}
			else
			{
				auto newIP = nCommandLabels.at((*nIP)->getIdentifier());
				assert((*newIP)->getType() == Command::Type::Label &&
					(*newIP)->getIdentifier() == (*nIP)->getIdentifier());
				std::cout << "Found jump/label identifier " + (*newIP)->getIdentifier() << std::endl;
				nIP = std::next(newIP);
			}
		}

		else if ((*nIP) != nullptr)		// normal case
		{
			(*nIP)->execute(nEngine);
			nIP++;
		}
	}

	// push to title state if instructions are over


	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	nEngine.handleEvent(event);

	return false;
}
