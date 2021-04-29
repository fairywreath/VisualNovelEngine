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
	Scanner(const std::string& scriptPath, const std::string& regPath, 
		CommandFactory& commandFactory, std::vector<CommandPtr>& commands);
	~Scanner();

	bool isComplete();
	void scanAll();
	
	void scan(bool script);

private:
	CommandFactory& nCommandFactory;

	std::ifstream nFile;
	std::string nScriptPath;
	std::string nRegPath;
	std::vector<CommandPtr>& nCommands;


};

#endif

