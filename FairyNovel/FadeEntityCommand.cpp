#include "FadeEntityCommand.hpp"
#include "Utility.hpp"
#include "Engine.hpp"

#include "Logger.hpp"

#include <iostream>

FadeEntityCommand::FadeEntityCommand(const std::string& id, const std::string& args) :
	Command(Command::Type::FadeEntity, id, args)
{
}

FadeEntityCommand::~FadeEntityCommand()
{
}

void FadeEntityCommand::execute(Engine& engine)
{
	std::vector<std::string> args = getArguments();

	float time = 0;				// time is automatically instant
	int start = INT_MAX;		// flag for entity fade cmd
	int target = 0;
	bool wait = false;			// wait is automatically false

	if (args[0] != "")
	{
		if (!isNumber(args[0]))
		{
			std::string message = "Fade Time does not have positve numeric target alpha value: " + args[0];
			LOGGER->Log("Fade Entity Command", message);
			return;
		}
		time = stof(args[0]);
	}

	if (args[1] == "" || !isNumber(args[1]))
	{
		std::string message = "Fade target does not have positve numeric target alpha value: " + args[1];
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
			std::string message = "Fade Command must have target alpha value";
			LOGGER->Log("Fade Entity Command", message);
			return;
		}
	}

	std::cout << "Fade args all valid\n";

	Entity* ent = engine.getEntity(getIdentifier());
	if (ent)
	{
		ent->fade(time, target, start);
		if (wait)
			engine.setWaitAnimation(true);
	}
	else
	{
		std::string msg = "Entity ID not found: " + getIdentifier();
		LOGGER->Log("Fade Entity Command", msg);
	}
}

std::vector<std::string> FadeEntityCommand::getArguments() const
{
	// maximum 4 args
	// index 0  for time
	// index 2 for target alpha
	// index 3 for starting alpha
	// index 4 for animation wait(in engine)
	std::vector<std::string> args(4, "");

	std::vector<std::string> splt = split(getArgumentString(), ';');
	std::cout << "Split size: " << splt.size() << std::endl;

	for (auto& arg : splt)
	{
		std::vector<std::string> currSplt = split(arg, ':');

		if (currSplt.size() != 2)
		{
			std::string message = "Invalid Fade Argument: " + arg;
			LOGGER->Log("Fade Entity Command", message);
			continue;
		}

		currSplt[0] = trim(currSplt[0]);
		currSplt[1] = trim(currSplt[1]);
		
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
		else
		{
			args[index] = currSplt[1];
		}
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
			
