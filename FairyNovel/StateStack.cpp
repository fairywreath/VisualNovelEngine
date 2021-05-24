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
	//for (auto itr = nStack.rbegin(); itr != nStack.rend(); itr++)
	//{
	//	if (!(*itr)->handleEvent(event))
	//	{
	//		break;
	//	}

	//}
	if (!nStack.empty())
	{
		(*nStack.rbegin())->handleEvent(event);
	}
	

	applyPendingChanges();
}


void StateStack::update(sf::Time dt)
{
	//for (auto itr = nStack.rbegin(); itr != nStack.rend(); itr++)
	//{
	//	if (!(*itr)->update(dt))		
	//		break;
	//}

	if (!nStack.empty())
	{
		(*nStack.rbegin())->update(dt);
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	//for (const auto& state : nStack)
	//{
	//	state->draw();
	//}
	if (!nStack.empty()) (*nStack.rbegin())->draw();
}


void StateStack::applyPendingChanges()
{
	for (const PendingChange& change : nPendingList)
	{
		switch (change.action)
		{
		case Action::Push:
		{
			nStack.push_back(createState(change.stateID));			
			break;
		}

		case Action::Pop:
		{
			nStack.pop_back();
			if (!nStack.empty())
			{
				(*nStack.rbegin())->refresh();
			}
			break;
		}
		case Action::Clear:
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
	nPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	nPendingList.push_back(PendingChange(Action::Pop));				
}

void StateStack::clearStates()
{
	nPendingList.push_back(PendingChange(Action::Clear));		
}

bool StateStack::isEmpty() const
{
	return nStack.empty();
}
