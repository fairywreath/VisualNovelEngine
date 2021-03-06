#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "CommandFactory.hpp"

#include <SFML/System/NonCopyable.hpp>

#include <fstream>
#include <vector>
#include <unordered_map>

/* Description:
the scanner parses the script and returns the command
*/

class Scanner : private sf::NonCopyable
{
public:
	using CommandPtr = std::unique_ptr<Command>;
	using CommandLbl = std::vector<CommandPtr>::const_iterator;

public:
	Scanner(const std::string& scriptPath, const std::string& regPath, 
		CommandFactory& commandFactory, std::vector<CommandPtr>& commands,
		std::unordered_map<std::string, CommandLbl>& commandLabels);
	
	~Scanner();
	Scanner(const Scanner&) = delete;
	Scanner& operator=(const Scanner&) = delete;

	bool isComplete();
	void scanCommands(bool script = true);

private:
	void scan(bool script);
	

private:
	CommandFactory& nCommandFactory;

	std::ifstream nFile;
	std::string nScriptPath;
	std::string nRegPath;
	std::vector<CommandPtr>& nCommands;
	std::unordered_map<std::string, CommandLbl>& nCommandLabels;
};

#endif

