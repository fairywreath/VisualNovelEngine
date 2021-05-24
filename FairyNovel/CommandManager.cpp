#include "CommandManager.hpp"

#include "Logger.hpp"

CommandManager::CommandManager() :
	nCommands(),
	nCommandLabels(),
	nBacklogCommands(),
	nIP(nCommands.begin()),
	nEngine(nullptr)
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







