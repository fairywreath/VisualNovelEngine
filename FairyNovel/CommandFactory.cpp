#include "CommandFactory.hpp"
#include "RegisterCommand.hpp"
#include "DisplaySpriteCommand.hpp"
#include "DisplayTextCommand.hpp"
#include "RemoveSpriteCommand.hpp"
#include "PlayMusicCommand.hpp"
#include "PlaySoundCommand.hpp"
#include "JumpCommand.hpp"
#include "LabelCommand.hpp"
#include"FadeEntityCommand.hpp"
#include "BlurEntityCommand.hpp"
#include "MoveEntityCommand.hpp"

#include "Logger.hpp"

#include <stdexcept>
#include <iostream>

CommandFactory::CommandPtr CommandFactory::generateCommand(const std::string& kw, const std::string& id, 
    const std::string& args)
{
    if (kw == "DisplayText")
    {
        // redundant type change later :pp
        return std::make_unique <DisplayTextCommand>(Command::Type::DisplayText, id, args);
    }
    else if (kw == "DisplaySprite")
    {
        return std::make_unique<DisplaySpriteCommand>(Command::Type::DisplaySprite, id, args);
    }
    else if (kw == "RemoveSprite")
    {
        return std::make_unique<RemoveSpriteCommand>(Command::Type::RemoveSprite, id, args);
    }
    else if (kw == "PlayMusic")
    {
        return std::make_unique<PlayMusicCommand>(Command::Type::PlayMusic, id, args);
    }
    else if (kw == "PlaySound")
    {
        return std::make_unique<PlaySoundCommand>(Command::Type::PlaySound, id, args);
    }
    else if (kw == "Label")
    {
        return std::make_unique<LabelCommand>(id, args);
    }
    else if (kw == "Jump")
    {
        return std::make_unique<JumpCommand>(id, args);
    }
    else if (kw == "FadeEntity")
    {
        return std::make_unique<FadeEntityCommand>(id, args);
    }
    else if (kw == "MoveEntity")
    {
        return std::make_unique<MoveEntityCommand>(id, args);
    }
    else
    {
    throwError("Command Read", "Unrecognized script Keyword");
    return CommandPtr();
    }
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
