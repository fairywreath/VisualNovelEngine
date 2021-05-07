#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "State.hpp"
#include "Entity.hpp"
#include "Character.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include <list>

class Engine : public sf::Drawable, private sf::NonCopyable
{
public:
	using EntityPtr = std::unique_ptr<Entity>;

public:
	Engine(State::Context context);

	void update(sf::Time dt);

	bool handleEvent(const sf::Event& event);

	void playMusic(const std::string& id);
 	void playSound(const std::string& id);
	void stopMusic();

	void setDialogueSpeed(int amount);
	void setAuto(bool autoState);

	void skipDialogueLine();
	
	void skipAnimations();
	bool isInAnimation() const;
	bool shouldWait() const;

	void setBackground(const std::string& id);
	void displayText(const std::string& text, const std::string& name);

	void addEntity(EntityPtr entity);
	void addEntity(const std::string& id, const std::string& texture, const sf::Vector2f& pos);
	void removeEntity(const std::string& id);

	// can remove all of these later and just use getEntity())
	// run this from commands if possible use getEntity
	// void fadeEntity(const std::string& id, float time, int targetAlpha, int startingAlpha = 0);
	// void moveEntity(const std::string& id, float time, const sf::Vector2f& dest, const sf::Vector2f& source = sf::Vector2f(FLT_MAX, FLT_MAX));
	
	void fadeScreen(float time, int targetAlpha, int startAlpha = INT_MAX);
	
	void setDialogueBoxOpacity(float amount);
	void setWait(bool w);
	void setWaitAnimation(bool w);

	void clearTransparentEntities();

	Entity* getEntity(const std::string& id);
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	MusicPlayer& nMusicPlayer;
	SoundPlayer& nSoundPlayer;
	TextureManager& nTextures;
	sf::Font& nFont;		// most likely can be removed later

	Entity nDialogueBox;
	Entity nBackground;		// derive entity class later for zoom effects

	std::vector<EntityPtr> nEntities;

	sf::Text nText;
	sf::Text nCharName;

	// change to time
	sf::Clock nTextClock;
	sf::Clock nDelayClock;
	sf::Time nTextTime;
	sf::Time nDelayTime;

	float nDialogueBoxOpacity;		// percentage later?

	int nDialogueSpeed;
	int nTextInterval;			
	static const int BaseInterval;

	int nDelay;	
	int nDelaySpeed;
	static const int BaseDelay;

	std::string nTextString;
	bool nLinePrinted;
	std::string::size_type nTextPos;

	// engine states
	bool nAutoMode;
	bool nWait;
	bool nAnimationWait;

	float nFadeTime;		// fade whole screen
	bool nInFade;
	bool nHideDialogueBox;
};

#endif