#include "Scanner.hpp"
#include "Utility.hpp"
#include "Logger.hpp"

#include <cassert>

#include <SFML/System/Clock.hpp>

#include <stdexcept>
#include <iostream>

Scanner::Scanner(const std::string& scriptPath, const std::string& regPath, 
		CommandFactory& commandFactory, std::vector<CommandPtr>& commands) :
	nScriptPath(scriptPath),
	nRegPath(regPath),
	nCommandFactory(commandFactory),
	nCommands(commands),
	nFile()
{
}

Scanner::~Scanner()
{
	if (nFile.is_open()) nFile.close();
}

bool Scanner::isComplete()
{
	return nFile.eof();
}

void Scanner::scanAll()
{
	scan(false);
	scan(true);
}

void Scanner::scan(bool script)
{
	sf::Clock clock;

	std::string str = "";
	std::string kw = "";
	std::string id = "";
	std::string args = "";

	if (script)
	{
		nFile.open(nScriptPath);
		if (!nFile.good())
		{
			nFile.clear();
			throw std::runtime_error("Could not open script file");
		}
		std::cout << "<<< SCRIPT SCAN START >>>\n";
	}
	else
	{
		nFile.open(nRegPath);
		if (!nFile.good())
		{
			nFile.clear();
			throw std::runtime_error("Could not open reg file");
		}
		std::cout << "<<< REG SCAN START >>>\n";
	}

	while (std::getline(nFile, str))
	{
		str = trim(str);
		if (str.size() == 0 || str[0] == '#') continue;		// commented line
		
		// std::cout << "Line: "  << str << std::endl;
		
		std::vector<size_t> spaces;

		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ') spaces.push_back(i);
			if (spaces.size() >= 2) break;
		}

		if (spaces.size() == str.size()) continue;		// empty line

		if (!spaces.empty())
		{
			kw = str.substr(0, spaces[0]);
			if (spaces.size() < 2)
			{
				id = str.substr(spaces[0] + 1, str.size() - spaces[0] - 1);
				args = "";
			}
			else
			{
				id = str.substr(spaces[0] + 1, spaces[1] - spaces[0] - 1);
				args = str.substr(spaces[1] + 1, str.size() - spaces[1] - 1);
			}
			
			if (!checkEnds(kw, '<', '>'))
				throw std::runtime_error("Keywords must have closing <> brackets");
			if (!checkEnds(id, '(', ')'))
				throw std::runtime_error("Identifiers must have closing () brakets");
			if (!checkEnds(args, '"', '"'))
				throw std::runtime_error("Arguments must have closing quotation marks ");

			if (script)
				nCommands.push_back(std::move(nCommandFactory.generateCommand(kw, id, args)));
			else
				nCommands.push_back(std::move(nCommandFactory.generateRegCommand(kw, id, args)));

			std::cout << "KW: " << kw << " ID: " << id << " Args: " << args << std::endl;
		}
		else
		{
			nFile.clear();
			throw std::runtime_error("Script Commands must contain valid spaces");
		}
	}

	nFile.close();
	nFile.clear();
}
