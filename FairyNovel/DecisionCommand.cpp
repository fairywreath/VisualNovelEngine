#include "DecisionCommand.hpp"
#include "Logger.hpp"
#include "Utility.hpp"


DecisionCommand::DecisionCommand(const std::string& identifier, const std::string& args) :
	Command(Type::Decision, identifier, args),
	nDecisions(Util::getCommandArgumentPairs(args))
{

}

void DecisionCommand::execute(Engine& engine)
{
	/*
	@the question is at the identifier, or maybe question not needed? already in dialogue box?
	*/
	auto nonErrorFound = std::find_if(nDecisions.cbegin(), nDecisions.cend(),
		[&](const auto& decision) {
			return (decision.first != "error");
		});

	if (nonErrorFound == nDecisions.cend())
	{
		// log
		// engine.setWait(false);
		return;
	}

	engine.setDecisionState();

	for (const auto& decision : nDecisions) 
	{
		engine.addDecisionButton(decision.first, decision.second);
	}

	engine.setWait(true);
}

std::vector<std::string> DecisionCommand::getArguments() const
{
	return Util::split(getArgumentString(), ';');
}


