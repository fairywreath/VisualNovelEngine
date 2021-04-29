#ifndef ENGINE_HPP
#define ENGINE_HPP

// all game logic
#include "State.hpp"
#include "Entity.hpp"

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
	typedef std::unique_ptr<Entity> EntityPtr;

public:
	Engine(State::Context context);

	void update(sf::Time dt);

	bool handleEvent(const sf::Event& event);

	void playMusic(const std::string& id);
// 	void playSound(const std::string& id;

	void setDialogueSpeed(int amount);
	void setAuto(bool autoState);

	void skipDialogueLine();

	bool shouldWait() const;

	// to be run by commands
	void setBackground(const std::string& id);
	void displayText(const std::string& text, const std::string& name);

	void displaySprite(const std::string& id, const sf::Vector2f& pos);
	void removeSprite(const std::string& id);


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	enum class CommandState
	{
		None,
		ShowDialogue,
		ShowAnimation
	};

private:
	MusicPlayer& nMusicPlayer;
	SoundPlayer& nSoundPlayer;
//	DialoguePlayer& nDialoguePlayer;		// TODO
	TextureManager& nTextures;
	sf::Font& nFont;		// most likely can be removed later

	sf::Sprite nBackground;
	sf::Sprite nDialogueBox;

	// possible change to unique_ptr for covariance
	std::list<EntityPtr> nEntities;

	sf::Text nText;
	sf::Text nCharName;

	sf::Clock nTextClock;
	sf::Clock nDelayClock;

	float nDialogueBoxOpacity;		// percentage

	int nDialogueSpeed;
	int nTextInterval;			// in ms
	static const int BaseInterval;

	int nDelay;		// delay in ms
	int nDelaySpeed;
	static const int BaseDelay;

	std::string nTextString;
	bool nLinePrinted;
	std::string::size_type nTextPos;

	// engine states
	bool nAutoMode;
	bool nWait;

	// TODO
	int nFade;
	bool nHideText;
	bool nFadeOn;
};

#endif