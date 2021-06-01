#include "StateStack.hpp"

#include <cassert>
#include <iostream>


StateStack::StateStack(State::Context context) :
	nStack(),				
	nPendingList(),
	nContext(context),
	nFactories(),
	nTimedChangeList()
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
	for (auto itr = nTimedChangeList.begin(); itr != nTimedChangeList.end();)
	{
		(*itr).time += dt;
		if ((*itr).time.asSeconds() >= (*itr).duration)
		{
			(*itr).statePtr->setUpdateState((*itr).updateState);
			itr = nTimedChangeList.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	int count = 0;
	for (auto itr = nStack.rbegin(); itr != nStack.rend();)
	{
		State::UpdateState state = (*itr)->getUpdateState();

		if (state == State::UpdateState::ShouldBeRemoved)
		{
			itr = decltype(itr)(nStack.erase(std::next(itr).base()));
			continue;
		}

		
		if (state != State::UpdateState::DoNotUpdate && state != State::UpdateState::DoNotUpdateAndDraw)
		{
			count++;
			(*itr)->update(dt);
		}

		itr++;
	}
//	std::cout << " num updated: " << count << std::endl;
	applyPendingChanges();
}

void StateStack::draw()
{
	int count = 0;

	for (auto itr = nStack.begin(); itr != nStack.end(); itr++)
	{
		State::UpdateState state = (*itr)->getUpdateState();
		if (state == State::UpdateState::DoNotUpdateAndDraw || state == State::UpdateState::ShouldBeRemoved)
		{
			continue;
		}
		count++;
		(*itr)->draw();
	}
//	std::cout << " num drawn: " << count << std::endl;

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
				if ((nStack.back()->getUpdateState() != State::UpdateState::InRemovalAnimation) &&
					(nStack.back()->getUpdateState() != State::UpdateState::ShouldBeRemoved))
				{
					nStack.back()->setUpdateState(State::UpdateState::DoNotUpdate);
					nTimedChangeList.push_back(TimedChange(nStack.back().get(), State::UpdateState::DoNotUpdateAndDraw, 1.f));
				}
			}
			nStack.push_back(createState(change.stateID));		
			break;
		}

		case Action::Pop:
		{
			nStack.back()->setUpdateState(State::UpdateState::InRemovalAnimation);
			nTimedChangeList.push_back(TimedChange(nStack.back().get(), State::UpdateState::ShouldBeRemoved, 1.f));
			if (nStack.size() >= 2)
			{
				(*++nStack.rbegin())->setUpdateState(State::UpdateState::OnTop);
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

/*
	@misc structs
*/
StateStack::TimedChange::TimedChange(State* pointer, State::UpdateState updateState, float duration) :
	statePtr(pointer),
	updateState(updateState),
	duration(duration),
	time(sf::Time::Zero)
{
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) :
	action(action),
	stateID(stateID)
{

}