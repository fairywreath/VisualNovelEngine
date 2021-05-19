#include "Engine.hpp"
#include "Utility.hpp"
#include "Logger.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <iostream>

Engine::Engine(State::Context context) :
	nMusicPlayer(*context.musicPlayer),
	nTextures(*context.textures),
	nFont(context.fonts->get("overlock")),
	nSoundPlayer(*context.soundPlayer),
	nCharacterBPs(*context.characters),
	nLinePrinted(true),
	nTextPos(-1),
	nFadeTime(0),
	nInFade(false),
	nAutoMode(false),
	nDialogueSpeed(5),
	nTextTime(sf::Time::Zero),
	nDelayTime(sf::Time::Zero),
	nTextInterval(BaseInterval),
	nDelaySpeed(1),
	nDelay(BaseDelay),
	nDialogueBoxOpacity(50),
	nWait(false),
	nHideDialogueBox(false),
	nEntities(),
	nCharacters(),
	nDialogueBox("DialogueBox", context.textures->get("dialoguebox")),
	nBackground("Background", context.textures->get("MMBG"))
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
	float dbx = (float)context.window->getSize().x / 2 - (float)dbT.getSize().x / 2;
	float dby = (float)context.window->getSize().y - (float)dbT.getSize().y - 30.f;
	nDialogueBox.setPosition(dbx, dby);

	setDialogueBoxOpacity(nDialogueBoxOpacity);

	nEntities.reserve(10);			// RESERVE WITH THE SIZE OF THE SPRITES???

	nBackground.setPosition(0.f, 0.f);
}

bool Engine::addCharacter(const std::string& id)
{
	if (nCharacterBPs.find(id) == nCharacterBPs.end())
	{
		// log error
		return false;
	}
	nCharacters.push_back(std::make_unique<Character>(nCharacterBPs.at(id)));
	return true;
}

void Engine::draw(sf::RenderTarget& target, sf::RenderStates states)  const
{
	target.draw(nBackground, states);

	for (const auto& ch : nCharacters) target.draw(*ch, states);
	for (const auto& ent : nEntities) target.draw(*ent, states);
	
	target.draw(nDialogueBox, states);
	target.draw(nCharName, states);
	target.draw(nText, states);
}

void Engine::update(sf::Time dt)
{
	if (!nLinePrinted) nTextTime += dt;

	if (!nLinePrinted && nTextTime.asMilliseconds() > nTextInterval) {
		nTextTime += dt;
		nTextPos++;
		if (nTextPos >= nTextString.size()) {
			nLinePrinted = true;
			nDelayTime = sf::Time::Zero;
			nTextTime = sf::Time::Zero;
		}
		else {
			std::string str = nText.getString();
			str += nTextString[nTextPos];
			size_t pos = nTextPos;
			while (nTextString[pos] != ' ' && pos < nTextString.size()) pos++;

			sf::String wrapped = Util::wrapText(sf::String(str), 800, nFont, 35, (int)(pos - nTextPos));
			nText.setString(wrapped);
		}
		nTextTime = sf::Time::Zero;
	}
	else if (nAutoMode && nLinePrinted) {
		if (nDelayTime.asMilliseconds() > nDelay) {
			nWait = false;
		}
		else {
			nDelayTime += dt;
		}
	}
	else {
		// empty
	}

	nBackground.update(dt);
	nDialogueBox.update(dt);

	for (const auto& ent : nCharacters) ent->update(dt);
	for (const auto& ent : nEntities) ent->update(dt);

	// clearTransparentEntities();

	if (nAnimationWait)
	{
		if (isInAnimation()) nWait = true;
		else
		{
			nWait = false;
			nAnimationWait = false;
		}
	}
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
	//	if (isInAnimation()) skipAnimations();

		nWait = false;
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
	{
		// case to case basis???
		if (!nLinePrinted)
		{
			skipDialogueLine();
		}
	//	if (isInAnimation()) skipAnimations();

		nWait = false;
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

void Engine::stopMusic()
{
	nMusicPlayer.stop();
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
	sf::String wrapped = Util::wrapText(sf::String(nTextString), 800, nFont, 35, 0);
	nText.setString(wrapped);
	nLinePrinted = true;
	nDelayTime = sf::Time::Zero;
}

void Engine::skipAnimations()
{
	if (nBackground.inAnimation()) nBackground.skipAnimation();
	if (nDialogueBox.inAnimation()) nDialogueBox.skipAnimation();

	for (const auto& ent : nEntities)
	{
		if (ent->inAnimation()) ent->skipAnimation();
	}

	setWaitAnimation(false);
}

bool Engine::isInAnimation() const
{
	if (nBackground.inAnimation()) return true;
	if (nDialogueBox.inAnimation()) return true;

	for (const auto& ent : nEntities)
	{
		if (ent->inAnimation()) return true;
	}
	
	return false;
}


bool Engine::shouldWait() const
{
	return nWait;
}

void Engine::setBackground(const std::string& id) noexcept
{
	nBackground.setTexture(nTextures.get(id));
}

bool Engine::setBackground(const std::string& id, float time) noexcept
{
	if (!nTextures.contains(id))
	{
		return false;
	}

	if (time <= 0)
	{
		setBackground(id);
		nBackground.setOpacityAlpha(255);			// just to be safe
		return true;
	}

	//nBackground.setOpacityAlpha(0);
	nBackground.setTexture(nTextures.get(id));
	nBackground.fade(time, 255, 0);

	return true;
}

void Engine::clearBackground(float time) noexcept
{
	nBackground.fade(time, 0);
}

void Engine::clearDialogueBox()
{
	nLinePrinted = false;
	nWait = false;
	nText.setString("");
	nCharName.setString("");
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

bool Engine::addEntity(const std::string& id, const std::string& texture, const sf::Vector2f& pos, int opacity) noexcept
{
	if (!nTextures.contains(id))
	{
		return false;
	}

	EntityPtr ent = std::make_unique<Entity>(id, nTextures.get(texture));
	ent->setOpacityAlpha(opacity);
	ent->setPosition(pos);
	nEntities.push_back(std::move(ent));

	return true;
}

void Engine::removeEntity(const std::string& id)
{
	std::cout << "sprite to remove: " << id << std::endl;
	auto test = nEntities.cbegin();

	for (auto itr = nEntities.cbegin(); itr != nEntities.cend();)
	{
		if ((*itr)->getIdentifier() == id)
		{
			std::cout << "sprite found\n";
			itr = nEntities.erase(itr);
			//	return;		// remove all instances of the same identifier
		}
		else itr++;
	}
}


void Engine::fadeScreen(float time, int targetAlpha, int startAlpha)
{
	nBackground.fade(time, targetAlpha, startAlpha);
	nDialogueBox.fade(time, targetAlpha, startAlpha);

	for (const auto& ent : nEntities) ent->fade(time, targetAlpha, startAlpha);
}

void Engine::clearTransparentEntities()
{
	for (auto itr = nEntities.begin(); itr != nEntities.end(); )
	{
		if ((*itr)->getOpacityAlpha() <= 0)
		{
			itr = nEntities.erase(itr);
			std::cout << "aplha 0 entity removed\n";
		}
		else
			itr++;
	}

//	std::cout << "size after entity clerance: " << nEntities.size() << std::endl;
}

Character* Engine::getCharacter(const std::string& id)
{
	const auto ch = std::find_if(nCharacters.begin(), nCharacters.end(), [&id](const CharacterPtr& ptr)
		{
			return (ptr->getIdentifier() == id);
		});

	if (ch != nCharacters.end()) return (*ch).get();
	
	// add log errorhere
	return nullptr;
}

Entity* Engine::getEntity(const std::string& id)
{
	for (const auto& ent : nEntities)
	{
		if (ent->getIdentifier() == id)
			return ent.get();
	}

	return nullptr;
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
	nDialogueBox.setOpacityAlpha((int)alpha);
}

void Engine::setWait(bool w)
{
	nWait = w;
}

void Engine::setWaitAnimation(bool w)
{
	nAnimationWait = w;
	if (w) nWait = true;		// set wait true the first time around just in case
}
