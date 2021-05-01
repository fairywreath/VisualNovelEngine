#include "Engine.hpp"
#include "Utility.hpp"
#include "Character.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

// in milliseconds
const int Engine::BaseInterval = 70;
const int Engine::BaseDelay = 1700;

Engine::Engine(State::Context context) :
	nMusicPlayer(*context.musicPlayer),
	nTextures(*context.textures),
	nFont(context.fonts->get("overlock")),
	nSoundPlayer(*context.soundPlayer),
	nLinePrinted(true),
	nTextPos(-1),
	nFade(0),
	nFadeOn(false),
	nAutoMode(false),
	nDialogueSpeed(5),
	nTextInterval(BaseInterval),
	nDelaySpeed(1),
	nDelay(BaseDelay),
	nDialogueBoxOpacity(70),
	nWait(false),
	nHideText(false),
	nEntities()
{
	nDelay = BaseDelay / nDelaySpeed;
	nTextInterval = BaseInterval / nDialogueSpeed;

	// set up dialogue textures and fonts and text
	nText.setCharacterSize(35);
	nText.setPosition(260.f, 520.f);
	nText.setFillColor(sf::Color::Black);
	nText.setFont(context.fonts->get("overlock"));

	nCharName.setCharacterSize(35);
	nCharName.setPosition(130.f, 520.f);
	nCharName.setFillColor(sf::Color::Black);
	nCharName.setFont(context.fonts->get("overlock"));

	sf::Texture& dbT = nTextures.get("dialoguebox");
	nDialogueBox.setTexture(dbT);
	float dbx = (float)context.window->getSize().x / 2 - (float)dbT.getSize().x / 2;
	float dby = (float)context.window->getSize().y - (float)dbT.getSize().y - 30.f;
	nDialogueBox.setPosition(dbx, dby);

	setDialogueBoxOpacity(nDialogueBoxOpacity);

	nTextClock.restart();

	//displaySprite("mayuri1", sf::Vector2f(700.f, 40.f));

	//displayText("I love you Darren", "Mayuri");
	setBackground("MMBG");

	// removeSprite("mayuri1");

	auto ctr = std::make_unique<Character>("Mayuri", nTextures.get("mayuri1"), "default");
	ctr->setPosition(sf::Vector2f(900, 40));
	Character* ptr = ctr.get();
	nEntities.push_back(std::move(ctr));
	// ptr->setOpacityAlpha(255);
	ptr->fade(2, 255, 0);
	ptr->insertState("second", nTextures.get("mayuri2"));
	ptr->setState("second");
	ptr->setState("default");
	ptr->move(0.75, sf::Vector2f(700, 40));
}

void Engine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(nBackground, states);

	for (const auto& ent : nEntities) target.draw(*ent, states);


	target.draw(nDialogueBox, states);
	target.draw(nCharName, states);
	target.draw(nText, states);
}

void Engine::update(sf::Time dt)
{
	if (!nLinePrinted && nTextClock.getElapsedTime().asMilliseconds() > nTextInterval) {
		nTextPos++;
		if (nTextPos >= nTextString.size()) {
			nLinePrinted = true;
			// nWait = false;
			nDelayClock.restart();
		}
		else {
			std::string str = nText.getString();
			str += nTextString[nTextPos];

		//	std::cout << "Text added: " << str << std::endl;

			// get size of remaining word
			size_t pos = nTextPos;
			while (nTextString[pos] != ' ' && pos < nTextString.size()) pos++;

			sf::String wrapped = wrapText(sf::String(str), 800, nFont, 35, (int)(pos - nTextPos));
			nText.setString(wrapped);
		}
		nTextClock.restart();
	}
	else if (nAutoMode && nLinePrinted && nDelayClock.getElapsedTime().asMilliseconds() > nDelay) {
		// go to next line
		// eg.
		nWait = false;
	}

	// update all entities
	for (const auto& ent : nEntities) ent->update(dt);
}

bool Engine::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
	{
		// case to case basis???
		if (!nLinePrinted)
		{
			skipDialogueLine();
		}
		else if (nWait)
		{
			// std::cout << "detected\n";
			nWait = false;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
	{
		// case to case basis???
		if (!nLinePrinted)
		{
			skipDialogueLine();
		}
		else if (nWait)
		{
			// std::cout << "detected\n";
			nWait = false;
		}
	}
	return false;
}

void Engine::playMusic(const std::string& id)
{
	nMusicPlayer.play(id);
}

void Engine::playSound(const std::string& id)
{
	nSoundPlayer.play(id);
}

void Engine::setDialogueSpeed(int amount)
{
	if (amount < 1 && amount > 10) return;
	nDialogueSpeed = 5;
	nTextInterval = BaseInterval / nDialogueSpeed;
}

void Engine::setAuto(bool autoState)
{
	nAutoMode = autoState;
}

void Engine::skipDialogueLine()
{
	sf::String wrapped = wrapText(sf::String(nTextString), 800, nFont, 35, 0);
	nText.setString(wrapped);
	nLinePrinted = true;
	nDelayClock.restart();
}

bool Engine::shouldWait() const
{
	return nWait;
}

void Engine::setBackground(const std::string& id)
{
	nBackground.setTexture(nTextures.get(id));
}

void Engine::displayText(const std::string& text, const std::string& name)
{
	nTextString = text;
	nTextPos = -1;
	nLinePrinted = false;
	nWait = true;
	nText.setString("");
	nCharName.setString(name);
}

void Engine::displaySprite(const std::string& id, const sf::Vector2f& pos)
{
	// for now assume all to be added entities are new
	EntityPtr ent = std::make_unique<Entity>(id, nTextures.get(id));
	ent->setPosition(pos);
	nEntities.push_back(std::move(ent));
}

void Engine::removeSprite(const std::string& id)
{
	std::cout << "sprite to remove: " << id << std::endl;
	auto test = nEntities.begin();

	for (auto itr = nEntities.begin(); itr != nEntities.end(); itr++)
	{
		if ((*itr)->getIdentifier() == id)
		{
			std::cout << "sprite found\n";
			nEntities.erase(itr);
			return;
		}
	}
}

void Engine::addEntity(EntityPtr entity)
{
	nEntities.push_back(std::move(entity));
}

void Engine::setDialogueBoxOpacity(float amount)
{
	// set opacity, 100% = 225
	nDialogueBoxOpacity = amount;
	float alpha = (amount / (float)100) * (float)255;
	nDialogueBox.setColor(sf::Color(255, 255, 255, (int)alpha));
}

