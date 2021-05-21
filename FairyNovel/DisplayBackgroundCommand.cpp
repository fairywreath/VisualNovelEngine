#include "DisplayBackgroundCommand.hpp"
#include "Utility.hpp"

#include "Logger.hpp"

DisplayBackgroundCommand::DisplayBackgroundCommand(const std::string& id, const std::string& args) :
	Command(Type::DisplayBackground, id, args)
{
}

void DisplayBackgroundCommand::execute(Engine& engine)
{
	if (!engine.setBackground(getIdentifier()))
	{
		std::string msg = "Texture ID not found: " + getIdentifier();
		LOGGER->Log("Display background Command", msg);
		return;
	}

	/*
		@size of args is ensured to be 1
	*/
	std::string time = getArguments()[0];

	if (!Util::isNumber(time))
	{
		std::string msg = "Time argument value must be a number: " + time;
		LOGGER->Log("Display background Command", msg);
		return;
	}

	engine.fadeInBackground(std::stof(time));
}

std::vector<std::string> DisplayBackgroundCommand::getArguments() const
{
	/*
		only one argument, time
	*/
	std::vector<std::string> res(1, "");

	std::vector<std::string> args = Util::split(getArgumentString(), ';');

	if (args.size() != 1)
	{
		std::string msg = "Incorrect argument size, display background must have only 1 argument: " + getArgumentString();
		LOGGER->Log("DIsplay Background Command", msg);
		return res;
	}

	std::vector<std::string> splt = Util::splitAndTrim(args[0], ':');

	if ((splt.size() != 2) != (splt[0] != "Time"))
	{
		std::string msg = "Incorrect DIsplay Background argument: " + getArgumentString();
		LOGGER->Log("DIsplay Background Command", msg);
		return res;
	}

	res[0] = splt[1];

	return res;
}
