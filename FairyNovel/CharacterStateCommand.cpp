#include "CharacterStateCommand.hpp"
#include "Engine.hpp"
#include "Utility.hpp"
#include "Logger.hpp"

CharacterStateCommand::CharacterStateCommand(const std::string& identifier, 
	const std::string& arguments):
	Command(Type::ChangeCharacterState, identifier, arguments)
{
}

void CharacterStateCommand::execute(Engine& engine)
{
	Character* chr = engine.getCharacter(getIdentifier());

	if (chr == nullptr)
	{
		std::string msg = "character id not found: " + getIdentifier();
		LOGGER->Log("Character State Command", msg);
		return;
	}

	/*
	arguments will always be sized 2
	index 0: state string, allowed to be ""
	index 1: transition time
	index 2: wait status
	*/
	std::vector<std::string> args = getArguments();
	
	if (args[1] != "")
	{
		if (!Util::isNumber(args[1]))
		{
			std::string msg = "transition time must be a number: " + args[1];
			LOGGER->Log("Character State Command", msg);
		}
		else if (std::stof(args[1]) < 0)
		{
			std::string msg = "transition time cannot be negative: " + args[1];
			LOGGER->Log("Character State Command", msg);
		}
		else
		{
			// empty
		}
	}
	else
	{
		args[1] = "0";
	}

	if (!chr->setState(args[0], std::stof(args[1])))
	{
		std::string msg = "State identifier not found: " + args[1];
		LOGGER->Log("Character State Command", msg);
		return;
	}

	bool wait = false;
	if (args[2] != "")
	{
		if (args[2] == "True")
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
			LOGGER->Log("Character State Command", message);
			return;
		}
	}

	if (wait) engine.setWait(true);

	std::cout << "character state success\n";
}

std::vector<std::string> CharacterStateCommand::getArguments() const
{
	/*
	index 0: state string
	index 1: transition time
	index 2: wait status
	*/
	std::vector<std::string> args(3, "");
	std::vector<std::string> splt = Util::split(getArgumentString(), ';');

	// TODO: will change these log errors to proper functions
	for (const auto& arg : splt)
	{
		std::vector<std::string> currSplt = Util::split(arg, ':');

		if (currSplt.size() != 2)		// at least pos 
		{
			std::string message = "Invalid Character State Change Argument: " + arg;
			LOGGER->Log("Character State Command", message);
			continue;
		}

		currSplt[0] = Util::trim(currSplt[0]);
		currSplt[1] = Util::trim(currSplt[1]);

		currSplt[0] = Util::trim(currSplt[0]);
		currSplt[1] = Util::trim(currSplt[1]);

		int index = -1;
		if (currSplt[0] == "State")
			index = 0;
		else if (currSplt[0] == "Fade")
			index = 1;
		else if (currSplt[0] == "Wait")
			index = 2;
		else
		{
			std::string message = "Invalid Character State Change Argument Keyword: " + currSplt[0];
			LOGGER->Log("Character State Command", message);
			continue;
		}

		if (args[index] != "")
		{
			std::string message = "Argument already initialized: " + currSplt[0];
			LOGGER->Log("Character State Command", message);
			continue;
		}

		args[index] = currSplt[1];
	}

	return args;
}
