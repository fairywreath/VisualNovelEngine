#include "CommandManager.hpp"

#include "Logger.hpp"

CommandManager::CommandManager() :
	nCommands(),
	nCommandLabels(),
	nBacklogCommands(),
	nIP(nCommands.begin()),
	nEngine(nullptr),
	nPlayer(nullptr)
{
}

/*
	@run the commands
*/
void CommandManager::update(sf::Time dt)
{
	if (nEngine == nullptr) return;

	while (nIP != nCommands.cend() && (*nIP) == nullptr)
	{
		nIP++;
	}

	if (!nEngine->shouldWait() && nIP != nCommands.cend())
	{
		if ((*nIP)->getType() == Command::Type::Jump)
		{
			jumpCommandLabel((*nIP)->getIdentifier());
		}
		else if ((*nIP)->getType() == Command::Type::Decision)
		{
			/*
				@handle in gamestate UI
			*/
			// maybe fade and handle engine animations
			nEngine->setWait(true);
		}
		else 		// normal case
		{
			if ((*nIP)->getType() == Command::Type::DisplayText)
			{
				nBacklogCommands.push_back((*nIP).get());
			}

			(*nIP)->execute(*nEngine);
			nIP++;
		}
	}

}

std::vector<CommandManager::CommandPtr>& CommandManager::getCommands()
{
	return nCommands;
}

CommandManager::LabelMap& CommandManager::getCommandLabels()
{
	return nCommandLabels;
}

std::vector<Command*>& CommandManager::getBacklogCommands()
{
	return nBacklogCommands;
}

void CommandManager::restartIP()
{
	nIP = nCommands.cbegin();
}

void CommandManager::setEngine(Engine& engine)
{
	nEngine = &engine;
	restartIP();
}

void CommandManager::releaseEngine()
{
	nEngine = nullptr;
}

void CommandManager::jumpCommandLabel(const std::string& label) noexcept
{
	if (nCommandLabels.find(label) == nCommandLabels.cend())
	{
		std::string msg = "Could not find script label " + label + " after decision";
		LOGGER->Log("Decision/Command Jump error", msg);
		nIP++;				// skip to next command
		return;
	}
	
	auto newIP = nCommandLabels.at(label);
	assert((*newIP)->getType() == Command::Type::Label &&
		(*newIP)->getIdentifier() == label);
	
	nIP = std::next(newIP);
	nEngine->setWait(false);
}







