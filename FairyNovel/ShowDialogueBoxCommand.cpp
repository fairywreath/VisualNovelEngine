#include "ShowDialogueBoxCommand.hpp"
#include "Utility.hpp"

#include "Logger.hpp"

ShowDialogueBoxCommand::ShowDialogueBoxCommand(const std::string& id, const std::string& args) :
	Command(Type::ShowDialogueBox, id, args)
{
}

void ShowDialogueBoxCommand::execute(Engine& engine)
{
	/*
	@size of args is ensured to be 1
	*/
	std::string time = getArguments()[0];

	if (!Util::isNumber(time))
	{
		std::string msg = "Time argument value must be a number: " + time;
		LOGGER->Log("Show Dialogue Box Command", msg);
		return;
	}

	float alpha = (float)255.0 * (engine.getOpacityPercent() / (float)100.0);
	engine.fadeDialogueBox(std::stof(time), static_cast<int>(alpha));

	engine.setWaitAnimation(true);
}

std::vector<std::string> ShowDialogueBoxCommand::getArguments() const
{
	/*
		only one argument, time
	*/
	std::vector<std::string> res(1, "");

	std::vector<std::string> args = Util::split(getArgumentString(), ';');

	if (args.size() != 1)
	{
		std::string msg = "Incorrect argument size, Show Dialogue Box must have 1 argument: " + getArgumentString();
		LOGGER->Log("Show Dialogue Box Command", msg);
		return res;
	}

	std::vector<std::string> splt = Util::splitAndTrim(args[0], ':');

	if ((splt.size() != 2) || (splt[0] != "Time"))
	{
		std::string msg = "Incorrect Show Dialogue Box argument: " + getArgumentString();
		LOGGER->Log("Show Dialogue Box Command", msg);
		return res;
	}

	res[0] = splt[1];

	return res;
}
