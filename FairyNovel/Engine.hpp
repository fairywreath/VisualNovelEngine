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
#include <SFML/Graphics/RectangleShape.hpp>

/*
	@engine class for graphics and game logic, acts like a 'canvas'
*/

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

	/*
		@system/game implementations
	*/
	void playMusic(const std::string& id);
 	void playSound(const std::string& id);
	void stopMusic();

	void setDialogueSpeed(int amount);
	void setAuto(bool autoState);
	void skipDialogueLine();

	void setAutoSpeed(int amount);
	bool getAuto() const;
	
	/*
		@animation state
	*/
	void skipAnimations();
	bool isInAnimation() const;

	/*
		@set/fade/clear background image
		@setBackground without time arg is instant
	*/
	bool setBackground(const std::string& id);
	void clearBackground(float time) noexcept;
	void fadeInBackground(float time) noexcept;

	/*
		@fade/clear whole screen, including all entities except the textbox and bg
		@no starting opacity set, all starting opacity is current opacity
	*/
	void clearScreen(float time) noexcept;
	void fadeInScreen(float time) noexcept;

	/*
		@fade/hide dialouge box sprite
	*/
	void setDialogueBoxOpacityPercent(float amount);
	void setDialogueBoxOpacity(int alpha);
	void fadeDialogueBox(float time, int alpha);
	void fadeInDialogueBox(float time);			// restore to normal

	/*
		@cleanup
	*/
	void clearTransparentEntities();

	/*
		@dialogue box functionalities
	*/
	void clearDialogueBoxText();
	void displayText(const std::string& text, const std::string& name);
	float getOpacityPercent() const;

	/*
		@adding/getting/removing characters
	*/
	Character* getCharacter(const std::string& id);
	bool addCharacter(const std::string& id);
	void removeCharacter(const std::string& id);

	/*
		@adding/getting/removing entities
	*/
	Entity* getEntity(const std::string& id);
	bool addEntity(const std::string& id, const std::string& texture, const sf::Vector2f& pos);
	void removeEntity(const std::string& id);
	
	/*
		@wait command runs functionalties
	*/
	void setWait(bool w);
	void setWaitAnimation(bool w);
	bool shouldWait() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void fadeScreen(float time, int targetAlpha) noexcept;

private:
	static constexpr auto TextSize = 29;

private:
	static constexpr auto MaxTextWidth = 900;

	MusicPlayer& nMusicPlayer;
	SoundPlayer& nSoundPlayer;
	TextureManager& nTextures;
	sf::Font& nFont;		// most likely can be removed later
	std::unordered_map<std::string, CharacterBlueprint>& nCharacterBPs;

	sf::RectangleShape nTextWindow;

	Entity nTextBackground;
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
	static constexpr int BaseInterval = 30;
	static constexpr int TextSpeedDelta = 3;

	static constexpr int BaseDelay = 2200;
	static constexpr int DelaySpeedDelta = 200;

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