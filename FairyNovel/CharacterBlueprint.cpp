#include "CharacterBlueprint.hpp"

#include "Logger.hpp"

CharacterBlueprint::CharacterBlueprint(const std::string& id, const std::string& defState, 
	const std::string& defTexture, TextureManager& textures) :
	nIdentifier(id),
	nTextures(textures),
	nDefault(defState),
	nTexturesMap()
{
	insertState(defState, defTexture);
}

void CharacterBlueprint::insertState(const std::string& id, const std::string& texture)
{
	if (nTexturesMap.find(id) != nTexturesMap.end())
	{
		// state already exists, log and return
		return;
	}

	nTexturesMap.insert(std::make_pair(id, &nTextures.get(texture)));
}

bool CharacterBlueprint::stateExists(const std::string& state) const
{
	if (nTexturesMap.find(state) != nTexturesMap.end())
	{
		return true;
	}

	return false;
}

const sf::Texture& CharacterBlueprint::getTexture(const std::string& state) const noexcept
{
	// no except, state ALWAYS exists
	return *nTexturesMap.at(state);
}

std::string CharacterBlueprint::getDefaultState() const
{
	return nDefault;
}

std::string CharacterBlueprint::getIdentifier() const
{
	return nIdentifier;
}
