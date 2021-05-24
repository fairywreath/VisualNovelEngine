#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include "Command.hpp"
#include "DisplayTextCommand.hpp"

/*
	@stores and runs commands on engine
*/

class CommandManager
{
public:
	using CommandPtr = std::unique_ptr<Command>;
	using CommandLbl = std::vector<CommandPtr>::const_iterator;
	using LabelMap = std::unordered_map<std::string, CommandLbl>;


public:
	CommandManager();

	void update(sf::Time dt);

	std::vector<CommandPtr>& getCommands();
	LabelMap& getCommandLabels();
	std::vector<Command*>& getBacklogCommands();

	/*
		@restarts instruction pointer, eg. after a reserve
	*/
	void restartIP();

	void setEngine(Engine& engine);
	void releaseEngine();			// set to null

private:
	std::vector<CommandPtr>::const_iterator nIP;		// instruction pointer

	std::vector<CommandPtr> nCommands;
	LabelMap nCommandLabels;

	/*
		@pointers are assured to always exist, from unique_ptr of vector commands above
		@commands are all(currently) displaytext ones
		@getIdentifier and getArgumentString for name and dialogue respectively
	*/
	std::vector<Command*> nBacklogCommands;

	Engine* nEngine;
};


#endif