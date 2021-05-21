#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <vector>
#include <functional>
#include <map>

class Engine;

namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
	enum class Action	
	{
		Push,
		Pop,
		Clear
	};


public:
	explicit StateStack(State::Context context);			

	template <typename T>
	void registerState(States::ID stateID);

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);
	
	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;				// check state of the statestack

private:
	State::Ptr createState(States::ID stateID);

	void applyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, States::ID stateID = States::ID::None);			// set default to none if not given
		Action action;			
		States::ID stateID;
	};


private:
	std::vector<State::Ptr> nStack;				
	std::vector<PendingChange> nPendingList;			

	State::Context nContext;			
	std::map<States::ID, std::function<State::Ptr()>> nFactories;			

};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	nFactories[stateID] = [this]()				
	{
		return State::Ptr(new T(*this, nContext));		
	};
}



#endif
