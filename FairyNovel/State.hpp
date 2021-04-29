#ifndef STATE_HPP
#define STATE_HPP

#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"
#include "MusicPlayer.hpp"
#include "SoundPlayer.hpp"
#include "Config.hpp"
#include "Command.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>

namespace sf
{
	class RenderWindow;
}

class StateStack;			

class State
{
public:
	typedef std::unique_ptr<State> Ptr;		
	struct Context
	{
		Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts,
			MusicPlayer& music, SoundPlayer& sound, std::vector<std::unique_ptr<Command>>& commands);

		sf::RenderWindow* window;
		TextureManager* textures;
		FontManager* fonts;
		MusicPlayer* musicPlayer;
		SoundPlayer* soundPlayer;
		std::vector<std::unique_ptr<Command>>* commands;
	};

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;		
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

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

