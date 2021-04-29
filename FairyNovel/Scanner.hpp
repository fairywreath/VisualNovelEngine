#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "CommandFactory.hpp"

#include <SFML/System/NonCopyable.hpp>

#include <fstream>
#include <vector>

/* Description:
the scanner parses the script and returns the command
*/

class Scanner : private sf::NonCopyable
{
public:
	typedef std::unique_ptr<Command> CommandPtr;

public:
	Scanner(const std::string& scriptPath, CommandFactory& commandFactory, std::vector<CommandPtr>& commands);
	~Scanner();

	bool isComplete();
	void scan();

private:
	enum class ScanState
	{ 
		Inactive, 
		Register,
		Script
	};

private:
	CommandFactory& nCommandFactory;

	std::ifstream nFile;
	std::string nScriptPath;
	std::vector<CommandPtr>& nCommands;

	
	ScanState CurrentState;
};

#endif

