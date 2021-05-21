#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

#include "Engine.hpp"

class Command
{
public:
	enum class Type
	{
		RegisterTexture,
		RegisterSE,
		RegisterMusic, 
		RegisterFont,
		RegisterCharacter,
	//	RegisterTextBox,			// special case of texture
	//	RegisterButtonClick,
	//	RegisterButtonHover,
	//	RegisterTitleMusic,		// main menu music

		SetBackground,
		ClearDialogueBox,

		/*
			@game implementations
		*/
		DisplayText,
		Zoom,
		PlayMusic,
		PlaySound,
		ShowDialogueBox,
		HideDialogueBox,
		FadeOutBackground,
		DisplayBackground,
		
		/*
			@character implementations
		*/
		DisplayCharacter,
		ChangeCharacterState,

		/*
			@entity implementations, applies for characters except for DisplayEntity
			@character gets higher priority if ids are the same, they are checked first
		*/
		FadeEntity,
		BlurEntity,
		RemoveEntity,
		MoveEntity,
		DisplayEntity,

		// change these to entity
		DisplaySprite,		// need be removed?

		Label,
		Jump		// jump between labels, for decision making
	};

public:
	Command(Type type, const std::string& identifier, const std::string& arguments = "");
	virtual ~Command() = default;

	virtual void execute(Engine& engine) = 0;
	virtual std::vector<std::string> getArguments() const = 0;

	Type getType() const;
	std::string getIdentifier() const;
	std::string getArgumentString() const;

protected:
	// TODO for misc/logging, using logger singleton
	virtual void LoggerLog(const std::string& msg) const;

private:
	Type nType;
	std::string nIdentifier;
	std::string nArguments;

};

#endif

