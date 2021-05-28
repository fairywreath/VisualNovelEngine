#ifndef MAINMENUSTATE_HPP
#define MAINMENTUSTATE_HPP

#include "State.hpp"
#include "TextButton.hpp"
#include "Entity.hpp"

#include "Movable.hpp"
#include "Components.hpp"

class MainMenuState : public State
{
public:
	MainMenuState(StateStack& stack, Context context);
	~MainMenuState() override;

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

	void refresh() override;

private:
	void setButton(GUI::TextButton& btn);
	void packComponent(GUI::Component* cmp);

	void initialize();

	/*
		@maybe not needed really
	*/
	void setupButtons();

private:
	/*
		@manual variables for "slideshow"
	*/
	bool nBgDone;
	bool nTitleDone;

	/*
		@GUI background :p, so bad but who cares
	*/
	AnimatableRectShape nAnimeRect;
	Movable nRectMover;
	sf::RectangleShape nGUIWindow;

	/*
		@fadable entities
	*/
	Entity nBackground;
	Entity nTitle;

	static constexpr auto ButtonsX = 1080;
	static constexpr auto ButtonsDist = 90;
	static constexpr auto ButtonsStartY = 150;
	static constexpr auto ButtonCount = 5;
	/*
		GUI
	*/
	GUI::TextButton nStartBtn;
	GUI::TextButton nLoadgBtn;
	GUI::TextButton nConfigBtn;
	GUI::TextButton nGalleryBtn;
	GUI::TextButton nExitBtn;

	std::vector<GUI::Component*> nComponents;
};


#endif