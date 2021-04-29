#include "TitleState.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

TitleState::TitleState(StateStack& stack, Context context) :
	State(stack, context),
	nText(),
	nBackgroundSprite(),
	nShowText(true),
	nTextEffectTime(sf::Time::Zero)	
{
	if(context.musicPlayer->find("title")) context.musicPlayer->play("title");
	
	nText.setFont(context.fonts->get("overlock"));
	nText.setString("Press Any Key to Start");
	nText.setPosition(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().y / 2.f);
	nText.setCharacterSize(30);


//	nBackgroundSprite.setTexture(context.textures->get(Textures::NLADark));
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;			
	window.draw(nBackgroundSprite);

	if (nShowText) window.draw(nText);
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
		requestStackPop();	
		// requestStackPush(States::Game);
	}

	return true;
}
