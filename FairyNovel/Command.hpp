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
		Blur,
		Animation
	};

public:
	Command(Type type, const std::string& identifier, const std::string& arguments = "");
	virtual ~Command();

	virtual void execute(Engine& engine) = 0;

	Type getType() const;
	const std::string& getIdentifier() const;
	std::string getArgumentString() const;
	virtual std::vector<std::string> getArguments() = 0;

private:
	Type nType;
	std::string nIdentifier;
	std::string nArguments;


};

#endif

