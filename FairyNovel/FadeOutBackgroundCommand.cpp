#include "FadeOutBackgroundCommand.hpp"
#include "Utility.hpp"

#include "Logger.hpp"

FadeOutBackgroundCommand::FadeOutBackgroundCommand(const std::string& id, const std::string& args) :
	Command(Type::FadeOutBackground, id, args)
{
}

void FadeOutBackgroundCommand::execute(Engine& engine)
{
	/*
		@size of args is ensured to be 1
	*/
	std::string time = getArguments()[0];

	if (!Util::isNumber(time))
	{
		std::string msg = "Time argument value must be a number: " + time;
		LOGGER->Log("Fade background Command", msg);
		return;
	}

	engine.clearBackground(std::stof(time));
}

std::vector<std::string> FadeOutBackgroundCommand::getArguments() const
{
	/*
		only one argument, time
	*/
	std::vector<std::string> res(1, "");

	std::vector<std::string> args = Util::split(getArgumentString(), ';');
	
	if (args.size() != 1)
	{
		std::string msg = "Incorrect argument size, fade backgroudn must have only 1 argument: " + getArgumentString();
		LOGGER->Log("Fade background Command", msg);
		return res;
	}

	std::vector<std::string> splt = Util::splitAndTrim(args[0], ':');

	if ((splt.size() != 2) != (splt[0] != "Time"))
	{
		std::string msg = "Incorrect fade background argument: " + getArgumentString();
		LOGGER->Log("Fade background Command", msg);
		return res;
	}

	res[0] = splt[1];

	return res;
}
