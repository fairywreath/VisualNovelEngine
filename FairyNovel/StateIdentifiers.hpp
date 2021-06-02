#ifndef STATEIDENTIFIERS_HPP
#define STATEIDENTIFIERS_HPP

// identifiers for (screen) states
namespace States
{
	enum class ID
	{
		None,
		Title,
		MainMenu,
		Settings,
		Config,
		Game,
		Backlog,
		Save,
		Load,
		Gallery,
		ConfirmationPrompt
	};
}

#endif