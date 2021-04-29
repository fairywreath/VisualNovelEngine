#include "Scanner.hpp"
#include "Utility.hpp"

#include <cassert>

#include <SFML/System/Clock.hpp>

#include <stdexcept>
#include <iostream>

Scanner::Scanner(const std::string& scriptPath, CommandFactory& commandFactory, std::vector<CommandPtr>& commands) :
	nScriptPath(scriptPath),
	nCommandFactory(commandFactory),
	nCommands(commands),
	nFile(),
	CurrentState(ScanState::Inactive)
{
	nFile.open(scriptPath);
	if (!nFile.good())
	{
		nFile.clear();
		throw std::runtime_error("Could not open script file");
	}
}

Scanner::~Scanner()
{
	if (nFile.is_open()) nFile.close();
}

bool Scanner::isComplete()
{
	return nFile.eof();
}

void Scanner::scan()
{
	sf::Clock clock;


	std::string str = "";
	std::string kw = "";
	std::string id = "";
	std::string args = "";

	while (std::getline(nFile, str))
	{
		str = trim(str);
		if (str.size() == 0 || str[0] == '#') continue;		// commented line
		
		std::cout << "Line: "  << str << std::endl;
		
		std::vector<size_t> spaces;

		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == ' ') spaces.push_back(i);
			if (spaces.size() >= 2) break;
		}

		if (spaces.size() == str.size()) continue;		// empty line

		if (!spaces.empty())
		{
		/*	if(spaces.empty()) 
				throw std::runtime_error("Script Line must have valid spaces and arguments");*/
			if (CurrentState == ScanState::Inactive)
				throw std::runtime_error("Scanner must be in a valid state");

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

			if (CurrentState == ScanState::Register)
				nCommands.push_back(std::move(nCommandFactory.generateCommand(kw, id, args, true)));
			else
				nCommands.push_back(std::move(nCommandFactory.generateCommand(kw, id, args)));

			// debug
			//std::cout << "KW: [" << kw << "] ID: [" << id << "] Args: [" << args <<  "]" << std::endl;

			if(!checkEnds(kw, '<', '>'))
				throw std::runtime_error("Keywords must have closing <> brackets");
			if(!checkEnds(id, '(', ')'))
				throw std::runtime_error("Identifiers must have closing () brakets");
			if(!checkEnds(args, '"', '"'))
				throw std::runtime_error("Arguments must have closing quotation marks ");

			// debug
			//std::cout << "KW: " << kw << " ID: " << id << " Args: " << args << std::endl;
		}
		else
		{
			if (!spaces.empty()) str = str.substr(0, spaces[0]);
			if (str == "Register") CurrentState = ScanState::Register;
			else if (str == "Script")  CurrentState = ScanState::Script;
			else
				throw std::runtime_error("Unrecognized Script Mode, must be either Script or Register");
		}

	}

}
