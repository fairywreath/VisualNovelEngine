#include "StateStack.hpp"

#include <cassert>
#include <iostream>


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
	if (!nStack.empty())
	{
		(*nStack.rbegin())->handleEvent(event);
	}
	

	applyPendingChanges();
}


void StateStack::update(sf::Time dt)
{
	for (auto itr = nStack.rbegin(); itr != nStack.rend();)
	{
		State::UpdateState state = (*itr)->getUpdateState();

		if (state == State::UpdateState::ShouldBeRemoved)
		{
			itr = decltype(itr)(nStack.erase(std::next(itr).base()));
			continue;
		}

		
		if (state != State::UpdateState::DoNotUpdate)
		{
			(*itr)->update(dt);
		}

		itr++;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (auto itr = nStack.begin(); itr != nStack.end(); itr++)
	{
		State::UpdateState state = (*itr)->getUpdateState();
		if (state == State::UpdateState::DoNotUpdate || state == State::UpdateState::ShouldBeRemoved)
		{
			continue;
		}

		(*itr)->draw();
	}
}


void StateStack::applyPendingChanges()
{
	for (const PendingChange& change : nPendingList)
	{
		switch (change.action)
		{
		case Action::Push:
		{
			if (!nStack.empty())
			{
				nStack.back()->setUpdateState(State::UpdateState::InHideAnimation);
			}
			nStack.push_back(createState(change.stateID));			
			break;
		}

		case Action::Pop:
		{
			nStack.back()->setUpdateState(State::UpdateState::InRemovalAnimation);
			if (nStack.size() >= 2)
			{
				(*++nStack.rbegin())->setUpdateState(State::UpdateState::InShowAnimation);
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
