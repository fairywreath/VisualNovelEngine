#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

#include <string>

namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}


template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::SoundBuffer, std::string> SoundBufferManager;
typedef ResourceManager<sf::Texture, std::string> TextureManager;
typedef ResourceManager<sf::Font, std::string> FontManager;
typedef ResourceManager<sf::Shader, std::string> ShaderManager;

#endif

