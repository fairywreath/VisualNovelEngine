#include "StateStack.hpp"

#include <cassert>


StateStack::StateStack(State::Context context) :
	nStack(),				
	nPendingList(),
	nContext(context),
	nFactories()
{

}


State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = nFactories.find(stateID);
	assert(found != nFactories.end());			

	return found->second();					
}



void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = nStack.rbegin(); itr != nStack.rend(); itr++)
	{
		if (!(*itr)->handleEvent(event))
		{
			break;
		}

	}

	// apply stack operations after stack iteration above, when it is already safe
	applyPendingChanges();
}


void StateStack::update(sf::Time dt)
{
	for (auto itr = nStack.rbegin(); itr != nStack.rend(); itr++)
	{
		if (!(*itr)->update(dt))		
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (const auto& state : nStack)
	{
		state->draw();
	}
}


void StateStack::applyPendingChanges()
{
	for (const PendingChange& change : nPendingList)
	{
		switch (change.action)
		{
		case Push:
		{
			nStack.push_back(createState(change.stateID));			
			break;
		}

		case Pop:
			nStack.pop_back();		
			break;

		case Clear:
			nStack.clear();
			break;
		}
	}

	nPendingList.clear();
}


StateStack::PendingChange::PendingChange(Action action, States::ID stateID) :
	action(action),
	stateID(stateID)
{

}



void StateStack::pushState(States::ID stateID)
{
	nPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	nPendingList.push_back(PendingChange(Pop));				
}

void StateStack::clearStates()
{
	nPendingList.push_back(PendingChange(Clear));		
}

bool StateStack::isEmpty() const
{
	return nStack.empty();
}
