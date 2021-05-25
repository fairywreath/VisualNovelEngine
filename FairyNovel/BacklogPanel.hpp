#ifndef BACKLOGPANEL_HPP
#define BACKLOGPANEL_HPP

#include "Label.hpp"

namespace GUI
{

class BacklogPanel : public Component
{

public:
	BacklogPanel();
	explicit BacklogPanel(const sf::Font& font);
	BacklogPanel(const std::string& text, const std::string& identifier, const sf::Font& font);
	
	~BacklogPanel() override = default;

	void setIdentifier(const std::string& id);
	void setText(const std::string& id);
	void setFont(const sf::Font& font);

	/*
		@component member functions
	*/
	bool isSelectable() const override;
	void handleEvent(const sf::Event & event) override;

private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void refreshOrigins();

private:
	static constexpr auto FontSize = 24;
	static constexpr auto DistY = 20;

	Label nTextLabel;
	Label nIdLabel;

};

}


#endif