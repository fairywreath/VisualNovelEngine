#ifndef VOICEPLAYER_HPP
#define VOICEPLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <unordered_map>
#include <cmath>

/*
	@voice playing is implemented through
	sf::sound with a single sound buffer
	@only voice can be played at a time(as it should be for the novel)
	@since there will be MULTIPLE, thousands of different dialogue lines
	files are loaded at runtime
*/

class VoicePlayer : private sf::NonCopyable
{
public:
	VoicePlayer();

	void play(const std::string& filePath);			// play using default vol
	void play(const std::string& identifier, const std::string& filePath);
	void stop();

	void insertCharacter(const std::string& identifier);		// start at vol 7
	void setVolume(const std::string& identifier, float amount);
	
	float getVolume(const std::string& identifier) const;
	
	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

private:
	static constexpr auto ListenerZ = 300.f;
	static constexpr auto Attenuation = 8.f;
	static constexpr auto MinDistance2D = 200.f;
	static constexpr auto MinDistance3D = 360.5551f;			// based on equation below
	// kekL
	// static constexpr auto MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);

	static constexpr auto DefaultVolume = 60.f;
private:
	/*
		@voice volumes, based on CHARACTER IDENTIFIER NAMES 
	*/
	std::unordered_map<std::string, float> nCharacterVolumes;

	sf::SoundBuffer nBuffer;
	sf::Sound nSound;
};


#endif