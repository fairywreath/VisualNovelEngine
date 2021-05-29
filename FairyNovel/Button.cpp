#include "Button.hpp"

GUI::Button::Button(State::Context context) :
	nIsToggle(false),
	nSounds(*context.soundPlayer),
	nCallback()
{
}

void GUI::Button::setCallback(Callback callback)
{
	nCallback = callback;
}

void GUI::Button::setToggle(bool flag)
{
	nIsToggle = flag;
}

bool GUI::Button::isSelectable() const
{
	return true;
}

void GUI::Button::select()
{
	Component::select();
	// nSounds.play("ButtonClick");

	updateApperance(ButtonState::Hover);
}

void GUI::Button::deselect()
{
	Component::deselect();

	updateApperance(ButtonState::Normal);
}

void GUI::Button::activate()
{
	Component::activate();		

	if (nIsToggle)
	{
		updateApperance(ButtonState::Pressed);
	}

	if (nCallback)
		nCallback();

	if (!nIsToggle)
	{
		deactivate();
		deselect();
	}

	nSounds.play("ButtonClick");
}

void GUI::Button::deactivate()
{
	Component::deactivate();

	if (nIsToggle)
	{
		if (isSelected())	
		{
			updateApperance(ButtonState::Hover);
		}
		else
		{
			updateApperance(ButtonState::Normal);
		}
	}
}
