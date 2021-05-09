#ifndef BUTTON_HPP
#define BUTTON_HPP


#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>			

class SoundPlayer;

namespace GUI
{

	class Button : public Component
	{
	public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;				// button functions are all void()

		enum class ButtonState
		{
			Normal,
			Hover,
			Pressed			
		};

	public:
		explicit Button(State::Context context);

		void setCallback(Callback callback);
		void setToggle(bool flag);

		virtual bool isSelectable() const;

		virtual void select() override;
		virtual void deselect() override ;
		virtual void activate() override;
		virtual void deactivate() override;

		virtual void handleEvent(const sf::Event& event) = 0;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void updateApperance(ButtonState state) = 0;

	private:
		Callback nCallback;
	
		bool nIsToggle;
		SoundPlayer& nSounds;
	};


}


#endif