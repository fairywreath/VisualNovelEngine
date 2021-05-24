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
	using Ptr = std::shared_ptr<Button>;
	using Callback = std::function<void()>;				// button functions are all void()

	enum class ButtonState
	{
		Normal,
		Hover,
		Pressed			
	};

public:
	explicit Button(State::Context context);
	~Button() override = default;

	void setCallback(Callback callback);
	void setToggle(bool flag);

	bool isSelectable() const override;

protected:
	void select() override;
	void deselect() override;
	void activate() override;
	void deactivate() override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	virtual void updateApperance(ButtonState state) = 0;

private:
	Callback nCallback;
	
	bool nIsToggle;
	SoundPlayer& nSounds;
};


}


#endif