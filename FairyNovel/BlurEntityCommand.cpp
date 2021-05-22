#include "BlurEntityCommand.hpp"
#include "Utility.hpp"
#include "Logger.hpp"

BlurEntityCommand::BlurEntityCommand(const std::string& id, const std::string& args) :
	Command(Type::BlurEntity, id, args)
{
}

void BlurEntityCommand::execute(Engine& engine)
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
		LOGGER->Log("Blur Entity Command", msg);
		return;
	}


	std::vector<std::string> args = getArguments();
	float time{ 0 };
	float target{ 0 };
	float start{ FLT_MAX };

	if (args[0] != "")
	{
		if (!Util::isNumber(args[0])) {
			std::string msg = "Invalid time argument, must be a number: " + args[0];
			LOGGER->Log("Blur Entity Command", msg);
			return;
		}
		time = std::stof(args[0]);
	}

	if (args[1] != "")
	{
		if (!Util::isNumber(args[1])) {
			std::string msg = "Invalid target argument, must be a number: " + args[1];
			LOGGER->Log("Blur Entity Command", msg);
			return;
		}
		target = std::stof(args[1]);
	}
	else
	{
		std::string msg = "Target argument must be provided: " + args[1];
		LOGGER->Log("Blur Entity Command", msg);
		return;
	}

	if (args[2] != "")
	{
		if (!Util::isNumber(args[2])) {
			std::string msg = "Invalid start argument, must be a number: " + args[2];
			LOGGER->Log("Blur Entity Command", msg);
			return;
		}
		start = std::stof(args[2]);
	}

	bool wait{ true };
	if (args[3] != "")
	{
		if (args[3] == "True") {
			wait = true;
		} else if (args[3] == "False") {
			wait = false;
		} else {
			std::string msg = "Invalid wait argument, must be a number: " + args[3];
			LOGGER->Log("Blur Entity Command", msg);
			return;
		}
	}

	if (start != FLT_MAX) {
		ent->blur(time, target, start);
	} else {
		ent->blur(time, target);
	}

	if (wait) engine.setWaitAnimation(true);

	std::cout << "blur success\n";
}

std::vector<std::string> BlurEntityCommand::getArguments() const
{
	/*
		index 0 time
		index 1 target
		index 2 start, optional
		index 3 wait, optional
	*/
	std::vector<std::string> args(4, "");
	std::vector<std::string> splt = Util::split(getArgumentString(), ';');

	for (auto& arg : splt)
	{
		std::vector<std::string> curr = Util::splitAndTrim(arg, ':');

		if (curr.size() != 2)
		{
			std::string msg = "Invalid argument: " + arg;
			LOGGER->Log("Blur Entity command", msg);
			continue;
		}

		int index = -1;
		if (curr[0] == "Time") {
			index = 0;
		} else if (curr[0] == "Target") {
			index = 1;
		} else if (curr[0] == "Start") {
			index = 2;
		} else if (curr[0] == "Wait") {
			index = 3;
		} else {
			std::string msg = "Invalid argument keyword: " + curr[0];
			LOGGER->Log("Blur Entity command", msg);
			continue;
		}

		args[index] = curr[1];
	}

	return args;
}



