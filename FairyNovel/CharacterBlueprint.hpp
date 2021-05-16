#ifndef CHARACTERBLUEPRINT_HPP
#define CHARACTERBLUEPRINT_HPP

#include "ResourceIdentifiers.hpp"
#include "ResourceManager.hpp"

#include <unordered_map>

class CharacterBlueprint
{
public:
	CharacterBlueprint(const std::string& id, const std::string& defState, 
		const std::string& defTexture, TextureManager& textures);

	void insertState(const std::string& id, const std::string& texture);
	bool stateExists(const std::string& state);

	const sf::Texture& getTexture(const std::string& state) noexcept;

	std::string getDefaultState() const;
	std::string getIdentifier() const;

private:
	std::unordered_map<std::string, const sf::Texture*> nTexturesMap;
	std::string nIdentifier;
	std::string nDefault;

	TextureManager& nTextures;		// maybe we can remove this reference?
};


#endif