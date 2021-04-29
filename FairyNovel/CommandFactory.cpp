#include "CommandFactory.hpp"
#include "RegisterCommand.hpp"

#include "Logger.hpp"

#include <stdexcept>
#include <iostream>

CommandFactory::CommandPtr CommandFactory::generateCommand(const std::string& kw, const std::string& id, 
    const std::string& args)
{
     return CommandPtr();
}

CommandFactory::CommandPtr CommandFactory::generateRegCommand(const std::string& kw, const std::string& id, const std::string& args)
{
    if (kw == "Texture")
    {
        return std::make_unique<RegisterCommand>(Command::Type::RegisterTexture, id, args);
    }
    else if (kw == "Music")
    {
        return std::make_unique<RegisterCommand>(Command::Type::RegisterMusic, id, args);
    }
    else if (kw == "SoundEffect")
    {
       return std::make_unique<RegisterCommand>(Command::Type::RegisterSE, id, args);
    }
    else
    {
        throwError("Command Read", "Unrecognized Register Keyword");
        return CommandPtr();
    }
}

void CommandFactory::throwError(const std::string& tag, const std::string& msg)
{
    std::string message = msg;
    LOGGER->Log(tag, message);
    throw std::runtime_error("Error in command read: " + tag + " " + message);
}
