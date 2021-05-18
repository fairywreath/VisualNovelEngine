#include "DisplayCharacterCommand.hpp"
#include "utility.hpp"
#include "Engine.hpp"

#include "Logger.hpp"

DisplayCharacterCommand::DisplayCharacterCommand(const std::string& identifier, 
	const std::string& arguments):
	Command(Type::DisplayCharacter, identifier, arguments)
{
}

void DisplayCharacterCommand::execute(Engine& engine)
{
	if (!engine.addCharacter(getIdentifier()))
	{
		std::string msg = "character id not found: " + getIdentifier();
		LOGGER->Log("Display Character Command", msg);
		return;
	}

	Character* chr = engine.getCharacter(getIdentifier());
	auto args = getArguments();

	// position
	if (args[0] == "")
	{
		// no position, log and return
		std::string msg = "Character Display Position Not Given";
		LOGGER->Log("Display Character Command", msg);
		return;
	}
	
	auto posArr = split(args[0], ',');
	if (posArr.size() != 2)
	{
		std::string msg = "Invalid position coordinates: " + args[0];
		LOGGER->Log("Display Character Command", msg);
		return;
	}
	if (!Util::isNumber(posArr[0]) || !Util::isNumber(posArr[1]))
	{
		std::string msg = "Position coordinates must be numbers: " + args[0];
		LOGGER->Log("Display Character Command", msg);
		return;
	}

	for (auto& pos : posArr) pos = trim(pos);
	chr->setPosition(sf::Vector2f(std::stof(posArr[0]), std::stof(posArr[1])));

	// state, if given not default
	if (args[1] != "")
	{
		chr->setState(args[1]);
	}

	// fade
	if (args[2] != "")
	{
		args[2] = trim(args[2]);
		if (!Util::isNumber(args[2]))
		{
			std::string msg = "Fade time must be a number: " + args[0];
			LOGGER->Log("Display Character Command", msg);
			return;
		}

		Entity* ent = chr->getEntity();
		ent->fade(std::stof(args[2]), 255, 0);
	}

	// wait
	bool wait = false;
	if (args[3] != "")
	{
		if (args[3] == "True")
		{
			wait = true;
		}
		else if (args[3] == "False")
		{
			wait = false;
		}
		else
		{
			std::string message = "Invalid wait argument";
			LOGGER->Log("Display Character Command", message);
			return;
		}
	}

	if (wait) engine.setWait(true);
}

std::vector<std::string> DisplayCharacterCommand::getArguments() const
{
	// maximum 4 args
	// index 0  for pos
	// index 1 for state
	// index 2 for fade time
	// index 3 for animation wait(in engine)
	std::vector<std::string> args(4, "");

	std::vector<std::string> splt = split(getArgumentString(), ';');
	std::cout << "Split size: " << splt.size() << std::endl;

	for (const auto& arg : splt)
	{
		std::vector<std::string> currSplt = split(arg, ':');

		if (currSplt.size() != 2)		// at least pos 
		{
			std::string message = "Invalid Display Argument: " + arg;
			LOGGER->Log("Display Character Command", message);
			continue;
		}

		currSplt[0] = trim(currSplt[0]);
		currSplt[1] = trim(currSplt[1]);

		int index = -1;
		if (currSplt[0] == "Pos")
			index = 0;
		else if (currSplt[0] == "State")
			index = 1;
		else if (currSplt[0] == "Fade")
			index = 2;
		else if (currSplt[0] == "Wait")
			index = 3;
		else
		{
			std::string message = "Invalid Display Character Argument Keyword: " + currSplt[0];
			LOGGER->Log("Display Character Command", message);
			continue;
		}

		if (args[index] != "")
		{
			std::string message = "Display Character Argument Keyword Already Initialized: " + currSplt[0];
			LOGGER->Log("Display Character Command", message);
			continue;
		}

		args[index] = currSplt[1];
	}

	return args;
}
