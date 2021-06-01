#include "CommandFactory.hpp"
#include "RegisterCommand.hpp"
#include "DisplayEntityCommand.hpp"
#include "DisplayTextCommand.hpp"
#include "RemoveEntityCommand.hpp"
#include "PlayMusicCommand.hpp"
#include "PlaySoundCommand.hpp"
#include "JumpCommand.hpp"
#include "LabelCommand.hpp"
#include "FadeEntityCommand.hpp"
#include "BlurEntityCommand.hpp"
#include "MoveEntityCommand.hpp"
#include "DisplayEntityCommand.hpp"
#include "CharacterStateCommand.hpp"
#include "DisplayCharacterCommand.hpp"
#include "FadeEntityCommand.hpp"

#include "DisplayBackgroundCommand.hpp"
#include "FadeOutBackgroundCommand.hpp"
#include "ShowDialogueBoxCommand.hpp"
#include "HideDialogueBoxCommand.hpp"

#include "DecisionCommand.hpp"

#include "Logger.hpp"

#include <stdexcept>
#include <iostream>

CommandFactory::CommandFactory() :
    nFactories()
{
    /*
        @game system commands
    */
    registerCommand<PlayMusicCommand>("PlayMusic");
    registerCommand<PlaySoundCommand>("PlaySound");
    registerCommand<DisplayTextCommand>("DisplayText");
    registerCommand<DisplayBackgroundCommand>("DisplayBackground");
    registerCommand<FadeOutBackgroundCommand>("FadeOutBackground");
    registerCommand<ShowDialogueBoxCommand>("ShowDialogueBox");
    registerCommand<HideDialogueBoxCommand>("HideDialogueBox");

    /*
        @game entity commands
    */
    registerCommand<DisplayEntityCommand>("DisplayEntity");
    registerCommand<RemoveEntityCommand>("RemoveEntity");
    registerCommand<MoveEntityCommand>("MoveEntity");
    registerCommand<FadeEntityCommand>("FadeEntity");
    registerCommand<DisplayCharacterCommand>("DisplayCharacter");
    registerCommand<CharacterStateCommand>("CharacterState");
    registerCommand<BlurEntityCommand>("BlurEntity");

    /*
        @control flow commands
    */
    registerCommand<LabelCommand>("Label");
    registerCommand<JumpCommand>("Jump");
    registerCommand<DecisionCommand>("Decision");
    
}

CommandFactory::CommandPtr CommandFactory::generateCommand(const std::string& kw, const std::string& id,
    const std::string& args)
{
    auto found = nFactories.find(kw);
    if (found != nFactories.end())
    {
        return found->second(id, args);
    }

    std::string msg = "Unrecognized comand keyword: " + kw;
    LOGGER->Log("Command Factory", msg);
    return nullptr;
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
    else if (kw == "Character")
    {
        return std::make_unique<RegisterCommand>(Command::Type::RegisterCharacter, id, args);
    }
    else
    {
        throw std::runtime_error("Error in register command read: " + kw);
    }
}

