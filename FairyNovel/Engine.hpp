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

class Engine : public sf::Drawable, private sf::NonCopyable
{
public:
	using EntityPtr = std::unique_ptr<Entity>;
	using CharacterPtr = std::unique_ptr<Character>;

public:
	explicit Engine(State::Context context);

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	~Engine() = default;

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
	
	void fadeScreen(float time, int targetAlpha, int startAlpha = INT_MAX);
	
	void setDialogueBoxOpacity(float amount);
	void setWait(bool w);
	void setWaitAnimation(bool w);

	void clearTransparentEntities();

	// maybe change later for better implementation
	Character* getCharacter(const std::string& id);
	Entity* getEntity(const std::string& id);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Clock testClock;
	bool test1 = true;
	bool test2 = true;

	MusicPlayer& nMusicPlayer;
	SoundPlayer& nSoundPlayer;
	TextureManager& nTextures;
	sf::Font& nFont;		// most likely can be removed later

	Entity nDialogueBox;
	Entity nBackground;		// derive entity class later for zoom effects

	std::vector<CharacterPtr> nCharacters; // will change to reference
	
	std::vector<EntityPtr> nEntities;

	sf::Text nText;
	sf::Text nCharName;

	sf::Time nTextTime;
	sf::Time nDelayTime;

	float nDialogueBoxOpacity;		// percentage later?
	
	// in milliseconds
	static constexpr int BaseInterval = 70;
	static constexpr int BaseDelay = 1700;

	int nDialogueSpeed;
	int nTextInterval;			

	int nDelay;	
	int nDelaySpeed;

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