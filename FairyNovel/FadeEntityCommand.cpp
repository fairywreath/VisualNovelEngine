#include "FadeEntityCommand.hpp"
#include "Utility.hpp"
#include "Engine.hpp"

#include "Logger.hpp"

FadeEntityCommand::FadeEntityCommand(const std::string& id, const std::string& args) :
	Command(Command::Type::FadeEntity, id, args)
{
}

FadeEntityCommand::~FadeEntityCommand()
{
}

void FadeEntityCommand::execute(Engine& engine)
{
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

	for (auto& arg : args)
	{
		std::string curr;
		int index;

		std::vector<std::string> currSplt = split(arg, ':');
		
		if (currSplt.size() > 2)
		{

			continue;
		}

	}

	return std::vector<std::string>({"a"});
}
