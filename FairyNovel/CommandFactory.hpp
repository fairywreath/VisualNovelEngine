#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "Command.hpp"

#include <memory>
#include <unordered_map>
#include <functional>

class CommandFactory
{
public:
	using CommandPtr =  std::unique_ptr<Command>;

public:
	CommandFactory();

	CommandPtr generateCommand(const std::string& kw, const std::string& id, const std::string& args);
	CommandPtr generateRegCommand(const std::string& kw, const std::string& id, const std::string& args);

private:

	template<typename T>
	void registerCommand(const std::string& kw);

private:
	std::unordered_map<std::string, std::function<CommandPtr(const std::string& id, const std::string& args)>> nFactories;

};

template<typename T>
void CommandFactory::registerCommand(const std::string& kw)
{
	auto func = [](const std::string& id, const std::string& args) {
		return std::make_unique<T>(id, args);
	};

	nFactories.insert(std::make_pair(kw, func));
}



#endif

