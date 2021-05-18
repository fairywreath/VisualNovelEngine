#ifndef DECISION_HPP
#define DECISION_HPP

/*
	novel choices
*/

#include "SpriteButton.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace GUI
{

	class Decision : public Component
	{
	public:
		Decision(State::Context context, int amount);

	private:


	};

}


#endif