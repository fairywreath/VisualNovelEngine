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
	nUpdateState(UpdateState::OnTop),
	nInStopUpdate(false),
	nStopUpdateTime(sf::Time::Zero),
	nStopUpdateAmount(0.f),
	nInRemove(false)
{
}


State::~State()
{
	// do nothing here
}

bool State::update(sf::Time dt)
{
	if (nInStopUpdate)
	{
		nStopUpdateTime += dt;
		if (nStopUpdateTime.asSeconds() > nStopUpdateAmount)
		{
			if (nInRemove)
			{
				setUpdateState(UpdateState::ShouldBeRemoved);
			}
			else
			{
				setUpdateState(UpdateState::DoNotUpdate);
				nStopUpdateTime = sf::Time::Zero;
			}
			nInStopUpdate = false;
		}
	}

	return false;
}

void State::setUpdateState(UpdateState state)
{
	nUpdateState = state;
}

State::UpdateState State::getUpdateState() const
{
	return nUpdateState;
}

void State::stopUpdateAfter(float time)
{
	nInStopUpdate = true;
	nStopUpdateAmount = time;
}

void State::removeAfter(float time)
{
	stopUpdateAfter(time);
	nInRemove = true;
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



