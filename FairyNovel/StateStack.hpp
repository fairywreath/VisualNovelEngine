#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <list>
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
		PushAfter,
		Pop,
		PopAfter,
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
	void pushStateAfter(States::ID stateId, float duration);
	void popState();
	void popStateAfter(float duration);
	void clearStates();

	bool isEmpty() const;				// check state of the statestack

	static constexpr auto UpdateTime = 0.7f;

private:
	State::Ptr createState(States::ID stateID);

	void applyPendingChanges();

	void removeTimedChangesForState(State* state);

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, States::ID stateID = States::ID::None);			
		PendingChange(Action action, float duration,  States::ID stateID = States::ID::None);			
		Action action;			
		States::ID stateID;

		sf::Time time;
		float duration;
	};

	/*
		@change UpdateState of state
	*/
	struct TimedChange
	{
		TimedChange(State* pointer, State::UpdateState updateState, float duration);
		State* statePtr;
		State::UpdateState updateState;

		float duration;
		sf::Time time;
	};

	struct TimedStackChange
	{
		PendingChange pendingChange;
		sf::Time time;
	};

private:
	std::list<TimedChange> nTimedChangeList;
	std::list<State::Ptr> nStack;				
	std::list<PendingChange> nPendingList;			

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
