#include "Component.hpp"

namespace GUI
{
	Component::Component() :
		nIsSelected(false),
		nIsActive(false)
	{
	}

	Component::~Component()
	{
	}

	void Component::update(sf::Time dt)
	{
	}

	bool Component::isSelected() const
	{
		return nIsSelected;
	}

	bool Component::isActive() const
	{
		return nIsActive;
	}

	void Component::select()
	{
		nIsSelected = true;
	}

	void Component::deselect()
	{
		nIsSelected = false;
	}

	void Component::activate()
	{
		nIsActive = true;
	}


	void Component::deactivate()
	{
		nIsActive = false;
	}



}

