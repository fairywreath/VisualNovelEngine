#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

class Engine;

class Command
{
public:
	enum class Type
	{
		RegisterTexture,
		RegisterSE,
		RegisterMusic, 
		RegisterFont,
	//	RegisterTextBox,			// special case of texture
	//	RegisterButtonClick,
	//	RegisterButtonHover,
	//	RegisterTitleMusic,		// main menu music

		DisplayText,
		DisplaySprite,
		RemoveSprite,
		Blur,
		Animation,
		
		FadeEntity,
		BlurEntity,
		MoveEntity,
		Zoom,

		PlayMusic,
		PlaySound,

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

private:
	Type nType;
	std::string nIdentifier;
	std::string nArguments;

};

#endif

