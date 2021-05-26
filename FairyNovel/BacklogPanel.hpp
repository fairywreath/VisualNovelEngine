#ifndef BACKLOGPANEL_HPP
#define BACKLOGPANEL_HPP

#include "Label.hpp"

namespace GUI
{

class BacklogPanel : public Component
{

public:
	BacklogPanel();
	BacklogPanel(const std::string& text, const std::string& identifier, const sf::Font& font);
	
	~BacklogPanel() override = default;

	void setIdentifier(const std::string& id);
	void setText(const std::string& id);
	void setFont(const sf::Font& font);
	void setSize(int size);

	/*
		@component member functions
	*/
	bool isSelectable() const override;
	void handleEvent(const sf::Event & event) override;

private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void refreshOrigins();

private:
	static constexpr auto MaxTextWidth = 800;
	static constexpr auto DistY = 24;

	Label nTextLabel;
	Label nIdLabel;

	sf::Font nFont;
};

}


#endif