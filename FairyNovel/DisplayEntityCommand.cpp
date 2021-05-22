#include "DisplayEntityCommand.hpp"
#include "Utility.hpp"
#include "Engine.hpp"
#include "Logger.hpp"

#include <cassert>
#include <iostream>

DisplayEntityCommand::DisplayEntityCommand(const std::string& identifier, const std::string& arguments) :
	Command(Type::DisplayEntity, identifier, arguments),
	nPosition()
{
}

void DisplayEntityCommand::execute(Engine& engine)
{
	std::vector<std::string> args = getArguments();

	float fade{ 0 };
	sf::Vector2f target{ 0, 0 };
	bool wait{ true };

	if (args[0] != "")
	{
		std::vector<std::string> pos = Util::split(args[0], ',');
		if (pos.size() != 2)
		{
			std::string message = "Invalid target position format: " + args[1];
			LOGGER->Log("Display Entity Command", message);
			return;
		}
		for (auto& str : pos) Util::trim(str);

		if (!Util::isNumber(pos[0]) || !Util::isNumber(pos[1]))
		{
			std::string message = "Target position does not have numeric value: " + args[1];
			LOGGER->Log("Display Entity Command", message);
			return;
		}
		target.x = stof(pos[0]);
		target.y = stof(pos[1]);
	}
	else
	{
		std::string message = "Display Entity command requires target position: " + args[1];
		LOGGER->Log("Display Entity Command", message);
		return;
	}

	if (args[1] != "")
	{
		if (!Util::isNumber(args[1]))
		{
			std::string message = "Fade Time is must be a number: " + args[0];
			LOGGER->Log("Display Entity Command", message);
			return;
		}
		fade = stof(args[1]);
	}

	if (args[2] != "")
	{
		if (args[2] == "True")
		{
			wait = true;
		}
		else if (args[2] == "False")
		{
			wait = false;
		}
		else
		{
			std::string message = "Invalid wait argument";
			LOGGER->Log("Display Entity Command", message);
			return;
		}
	}

	if (!engine.addEntity(getIdentifier(), getIdentifier(), target))
	{
		std::string message = "Entity/Texture id not found";
		LOGGER->Log("Display Entity Command", message);
		return;
	}

	Entity* ent = engine.getEntity(getIdentifier());
	ent->fade(fade, 255, 0);

	if (wait) engine.setWaitAnimation(true);
}

std::vector<std::string> DisplayEntityCommand::getArguments() const
{
	/*
		index 0 for pos
		index 1 for time, default 0
		index 2 for wait, default false
	*/
	std::vector<std::string> args(3, "");
	std::vector<std::string> splt = Util::split(getArgumentString(), ';');

	for (auto& arg : splt)
	{
		std::vector<std::string> currSplt = Util::split(arg, ':');

		if (currSplt.size() != 2)
		{
			std::string message = "Invalid Argument: " + arg;
			LOGGER->Log("Display Entity Command", message);
			continue;
		}

		currSplt[0] = Util::trim(currSplt[0]);
		currSplt[1] = Util::trim(currSplt[1]);

		int index = -1;
		if (currSplt[0] == "Pos")
			index = 0;
		else if (currSplt[0] == "Fade")
			index = 1;
		else if (currSplt[0] == "Wait")
			index = 2;
		else
		{
			std::string message = "Invalid Argument Keyword: " + currSplt[0];
			LOGGER->Log("Display Entity Command", message);
			continue;
		}

		if (args[index] != "")
		{
			std::cout << args[index] << " at index " << index << std::endl;
			std::string message = "Argument Keyword Already Initialized: " + currSplt[0];
			LOGGER->Log("Display Entity Command", message);
			continue;
		}

		args[index] = currSplt[1];
	}

	return args;
}
