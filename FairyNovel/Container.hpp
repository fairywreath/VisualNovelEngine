#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Component.hpp"

#include <vector>
#include <memory>		

namespace GUI
{

class Container : public Component
{
public:
	using Ptr =  std::unique_ptr<Component>;

public:
	Container();

	void pack(Component::Ptr component);			

	bool isSelectable() const override;
	void handleEvent(const sf::Event& event) override;


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;		


private:
	std::vector<Component::Ptr> nComponents;		

};


}

#endif