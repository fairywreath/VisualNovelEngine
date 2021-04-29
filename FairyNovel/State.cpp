#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, 
	MusicPlayer& music, SoundPlayer& sound, std::vector<std::unique_ptr<Command>>& commands) :
	window(&window),		
	textures(&textures),
	fonts(&fonts),
	musicPlayer(&music),
	soundPlayer(&sound),
	commands(&commands)
{
}

State::State(StateStack& stack, Context context) :
	nStack(&stack),		// set statestack pointer
	nContext(context)		// initialize context
{
}


State::~State()
{
	// do nothing here
}

void State::requestStackPush(States::ID stateID)
{
	nStack->pushState(stateID);
}

void State::requestStackPop()
{
	nStack->popState();
}

void State::requestStateClear()
{
	nStack->clearStates();
}

State::Context State::getContext() const
{
	return nContext;
}



