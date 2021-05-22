#include "HideDialogueBoxCommand.hpp"
#include "Utility.hpp"

#include "Logger.hpp"


HideDialogueBoxCommand::HideDialogueBoxCommand(const std::string& id, const std::string& args) :
	Command(Type::HideDialogueBox, id, args)
{
}

void HideDialogueBoxCommand::execute(Engine& engine)
{
	/*
		@size of args is ensured to be 1
	*/
	std::string time = getArguments()[0];

	if (!Util::isNumber(time))
	{
		std::string msg = "Time argument value must be a number: " + time;
		LOGGER->Log("Hide Dialogue Box Command", msg);
		return;
	}

	engine.fadeDialogueBox(std::stof(time), 0);

	engine.setWaitAnimation(true);
}

std::vector<std::string> HideDialogueBoxCommand::getArguments() const
{
	/*
		only one argument, time
	*/
	std::vector<std::string> res(1, "");

	std::vector<std::string> args = Util::split(getArgumentString(), ';');

	if (args.size() != 1)
	{
		std::string msg = "Incorrect argument size, Hide Dialogue Box must have 1 argument: " + getArgumentString();
		LOGGER->Log("Hide Dialogue Box Command", msg);
		return res;
	}

	std::vector<std::string> splt = Util::splitAndTrim(args[0], ':');

	if ((splt.size() != 2) || (splt[0] != "Time"))
	{
		std::string msg = "Incorrect Hide Dialogue Box argument: " + getArgumentString();
		LOGGER->Log("Hide Dialogue Box Command", msg);
		return res;
	}

	res[0] = splt[1];

	return res;
}
