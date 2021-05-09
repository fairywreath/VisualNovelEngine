#include "TitleState.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

TitleState::TitleState(StateStack& stack, Context context) :
	State(stack, context),
	nText(),
	nBackgroundSprite(),
	nShowText(true),
	nTextEffectTime(sf::Time::Zero)	,
	button1(context),
	button2(context)
{
	if(context.musicPlayer->find("title")) context.musicPlayer->play("title");
	
	nText.setFont(context.fonts->get("overlock"));
	nText.setString("Press Any Key to Start");
	nText.setPosition(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().y / 2.f);
	nText.setCharacterSize(30);

	nBackgroundSprite.setTexture(context.textures->get("BG1"));

	button1.setText("Hitagi best girl");
	button2.setText("Hitagi is life");

	button1.setPosition(100.f, 200.f);
	button2.setPosition(100.f, 300.f);
	button1.setCallback([this]()
		{
			requestStackPop();;
			requestStackPush(States::Game);
		});
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;			
	// window.draw(nBackgroundSprite);

	if (nShowText) window.draw(nText);

	window.draw(button1);
	window.draw(button2);

}

bool TitleState::update(sf::Time dt)
{
	nTextEffectTime += dt;

	if (nTextEffectTime >= sf::seconds(0.5f))
	{
		nShowText = !nShowText;		
		nTextEffectTime = sf::Time::Zero;			
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
	{
		//requestStackPop();	
	//	requestStackPush(States::Game);
	}

	button1.handleEvent(event);
	button2.handleEvent(event);


	return true;
}
