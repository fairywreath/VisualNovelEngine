#include "FadeEntityCommand.hpp"
#include "Utility.hpp"
#include "Engine.hpp"

#include "Logger.hpp"

#include <iostream>

FadeEntityCommand::FadeEntityCommand(const std::string& id, const std::string& args) :
	Command(Command::Type::FadeEntity, id, args)
{
}

void FadeEntityCommand::execute(Engine& engine)
{
	Entity* ent = engine.getEntity(getIdentifier());
	if (ent == nullptr)
	{
		std::string msg = "Entity ID not found: " + getIdentifier();
		LOGGER->Log("Fade Entity Command", msg);
		return;
	}

	std::vector<std::string> args = getArguments();

	float time{ 0 };				// time is automatically instant
	int start{ INT_MAX };		// flag for entity fade cmd
	int target{ 0 };
	bool wait{ false };			// wait is automatically false

	if (args[0] != "")
	{
		if (!isNumber(args[0]) || stof(args[0]) < 0)
		{
			std::string message = "Fade Time must be a non negative number: " + args[0];
			LOGGER->Log("Fade Entity Command", message);
			return;
		}
		time = stof(args[0]);
	}

	if (args[1] == "" || !isNumber(args[1]))
	{
		std::string message = "Fade target alpha is not numeric: " + args[1];
		LOGGER->Log("Fade Entity Command", message);
		return;
	}
	target = stoi(args[1]);

	if (args[2] != "")
	{
		if (!isNumber(args[2]))
		{
			std::string message = "Fade starting alpha is not numeric: " + args[2];
			LOGGER->Log("Fade Entity Command", message);
			return;
		}
		start = stoi(args[2]);
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
			LOGGER->Log("Fade Entity Command", message);
			return;
		}
	}

	// std::cout << "Fade args all valid\n";

	
	ent->fade(time, target, start);
	if (wait)
		engine.setWaitAnimation(true);
}

std::vector<std::string> FadeEntityCommand::getArguments() const
{
	// maximum 4 args
	// index 0  for time
	// index 1 for target alpha
	// index 2 for starting alpha
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
			LOGGER->Log("Fade Entity Command", message);
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
			std::string message = "Invalid Fade Argument Keyword: " + currSplt[0];
			LOGGER->Log("Fade Entity Command", message);
			continue;
		}

		if (args[index] != "")
		{
			std::string message = "Fade Argument Keyword Already Initialized: " + currSplt[0];
			LOGGER->Log("Fade Entity Command", message);
			continue;
		}
		
		args[index] = currSplt[1];
	}

	return args;
}

bool FadeEntityCommand::isNumber(const std::string& str)
{
	bool pointFound = false;		// allow one decimal point
	return !str.empty() && std::find_if(str.begin(),
		str.end(), [&pointFound](unsigned char c) {
			if (c == '.')
			{
				if (pointFound) return true;
				pointFound = true;
				return false;
			}
			return !std::isdigit(c);
		}) == str.end();
}
			
