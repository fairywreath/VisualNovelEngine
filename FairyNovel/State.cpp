#include "State.hpp"
#include "StateStack.hpp"
#include "CommandManager.hpp"

State::Context::Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts,
	MusicPlayer& music, SoundPlayer& sound, CommandManager& commandManager,
	ConfigManager& configManager, CharacterManager& characterManager) :
	window(&window),		
	textures(&textures),
	fonts(&fonts),
	musicPlayer(&music),
	soundPlayer(&sound),
	configManager(&configManager),
	commandManager(&commandManager),
	characterManager(&characterManager)
{
}

State::State(StateStack& stack, Context context) :
	nStack(&stack),		
	nContext(context),
	nUpdateState(UpdateState::OnTop)
{
}


State::~State()
{
	
}

void State::setUpdateState(UpdateState state)
{
	nUpdateState = state;
}

State::UpdateState State::getUpdateState() const
{
	return nUpdateState;
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

void State::requestStackPushAfter(States::ID stateID, float duration)
{
	nStack->pushStateAfter(stateID, duration);
}

void State::requestStackPopAfter(float duration)
{
	nStack->popStateAfter(duration);
}

State::Context State::getContext() const
{
	return nContext;
}



