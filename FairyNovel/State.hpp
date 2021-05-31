#ifndef STATE_HPP
#define STATE_HPP

#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"
#include "MusicPlayer.hpp"
#include "SoundPlayer.hpp"
#include "Config.hpp"
#include "CharacterBlueprint.hpp"
#include "ConfigManager.hpp"
#include "CharacterManager.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>

#include <unordered_map>

namespace sf
{
	class RenderWindow;
}

class StateStack;			
class CommandManager;
class Command;

class State
{
public:
	using Ptr = std::unique_ptr<State>;		
	using CommandPtr = std::unique_ptr<Command>;
	using CommandLbl = std::vector<CommandPtr>::const_iterator;

	/*
		@dependency injection, possibly change later for better use
	*/
	struct Context
	{
		Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts,
			MusicPlayer& music, SoundPlayer& sound, CommandManager& commandManager,
			ConfigManager& configManager, CharacterManager& characterManager);

		sf::RenderWindow* window;
		TextureManager* textures;
		FontManager* fonts;
		MusicPlayer* musicPlayer;
		SoundPlayer* soundPlayer;
		ConfigManager* configManager;
		CommandManager* commandManager;
		CharacterManager* characterManager;
	};

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	State(const State&) = delete;
	State& operator=(const State&) = delete;

	virtual void draw() = 0;		
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

	/*
		@do right when current state is at the top
	*/
	virtual void refresh();

public:

	/*
		@for in between fades
	*/
	virtual void setToRemovalAnimation();
	
	bool inRemovalAnimation() const;
	void setShouldBeRemoved();
	bool shouldBeRemoved() const;

private:
	/*
		@for in between fades
	*/
	bool nInRemovalAnimation;
	bool nShouldBeRemoved;


protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack* nStack;			// pointer to state stack
	Context nContext;			// state context

};

#endif

