#ifndef COMPONENT_HPP
#define COMPONENT_HPP


#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace sf
{
	class Event;
}

namespace GUI
{

	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:
		using Ptr = std::shared_ptr<Component>;

	public:
		Component();
		virtual ~Component();

		virtual void update(sf::Time dt);

		virtual bool isSelectable() const = 0;
		bool isSelected() const;

		virtual void select();
		virtual void deselect();
		virtual bool isActive() const;
		virtual void activate();
		virtual void deactivate();

		virtual void handleEvent(const sf::Event& event) = 0;

	private:
		bool nIsSelected;
		bool nIsActive;

	};

}


#endif