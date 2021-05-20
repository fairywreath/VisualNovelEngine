#include "MoveEntityCommand.hpp"
#include "Utility.hpp"
#include "Logger.hpp"
#include "Entity.hpp"
#include "Engine.hpp"

// debug
#include <iostream>

MoveEntityCommand::MoveEntityCommand(const std::string& id, const std::string& args) :
	Command(Command::Type::MoveEntity, id, args)
{
}

void MoveEntityCommand::execute(Engine& engine)
{
	Entity* ent = nullptr;
	if (engine.getCharacter(getIdentifier()) != nullptr)
	{
		ent = engine.getCharacter(getIdentifier())->getEntity();
	}
	else
	{
		ent = engine.getEntity(getIdentifier());
	}

	if (ent == nullptr)
	{
		std::string msg = "Character/Entity ID not found: " + getIdentifier();
		LOGGER->Log("Fade Entity Command", msg);
		return;
	}

	std::vector<std::string> args = getArguments();

	float time{ 0 };
	sf::Vector2f target{ 0, 0 };
	sf::Vector2f start{ FLT_MAX, FLT_MAX };
	bool wait{ false };

	if (args[0] != "")
	{
		if (!Util::isNumber(args[0]))
		{
			std::string message = "Move Time must be a positive number: " + args[0];
			LOGGER->Log("Move Entity Command", message);
			return;
		}
		time = stof(args[0]);
	}

	if (args[1] != "")
	{
		std::vector<std::string> pos = Util::split(args[1], ',');
		for (auto& str : pos) Util::trim(str);
		
		if(!Util::isNumber(pos[0]) || !Util::isNumber(pos[1]))
		{
			std::string message = "Move target position does not have numeric value: " + args[1];
			LOGGER->Log("Move Entity Command", message);
			return;
		}
		target.x = stof(pos[0]);
		target.y = stof(pos[1]);
	}
	else
	{
		std::string message = "Move entity command requires target position: " + args[1];
		LOGGER->Log("Move Entity Command", message);
		return;
	}


	if (args[2] != "")
	{
		std::vector<std::string> pos = Util::split(args[2], ',');
		for (auto& str : pos) Util::trim(str);

		if (!Util::isNumber(pos[0]) || !Util::isNumber(pos[1]))
		{
			std::string message = "Move starting position does not have numeric value: " + args[1];
			LOGGER->Log("Move Entity Command", message);
			return;
		}
		start.x = stof(pos[0]);
		start.y = stof(pos[1]);
	}

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
			LOGGER->Log("Move Entity Command", message);
			return;
		}
	}

	if (start.x != FLT_MAX)
		ent->move(time, target, start);
	else
		ent->move(time, target);
	
	if (wait)
		engine.setWaitAnimation(true);
	
}

std::vector<std::string> MoveEntityCommand::getArguments() const
{
	// maximum 4 args
	// index 0  for time
	// index 1 for target position
	// index 2 for starting position
	// index 3 for animation wait(in engine)
	std::vector<std::string> args(4, "");
	
	std::vector<std::string> splt = Util::split(getArgumentString(), ';');
	std::cout << "Split size: " << splt.size() << std::endl;

	for (auto& arg : splt)
	{
		std::vector<std::string> currSplt = Util::split(arg, ':');

		if (currSplt.size() != 2)
		{
			std::string message = "Invalid Fade Argument: " + arg;
			LOGGER->Log("Move Entity Command", message);
			continue;
		}

		currSplt[0] = Util::trim(currSplt[0]);
		currSplt[1] = Util::trim(currSplt[1]);

		int index = -1;
		if (currSplt[0] == "Time")
			index = 0;
		else if (currSplt[0] == "Target")
			index = 1;
		else if (currSplt[0] == "Start")
			index = 2;
		else if (currSplt[0] == "Wait")
			index = 3;
		else
		{
			std::string message = "Invalid Move Argument Keyword: " + currSplt[0];
			LOGGER->Log("Move Entity Command", message);
			continue;
		}

		if (args[index] != "")
		{
			std::string message = "Move Argument Keyword Already Initialized: " + currSplt[0];
			LOGGER->Log("Move Entity Command", message);
			continue;
		}
		args[index] = currSplt[1];
	}


	return args;
}

