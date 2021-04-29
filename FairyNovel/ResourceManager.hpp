#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <string>
#include <map>
#include <cassert>
#include <stdexcept>
#include <memory>

template<typename Resource, typename Identifier>
class ResourceManager
{
public:
	void load(const Identifier& id, const std::string& filename);

	template <typename Parameter>
	void load(const Identifier& id, const std::string& filename, const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;		// from const pointer

private:
	std::map<Identifier, std::unique_ptr<Resource>> nResourceMap;

};

#include "ResourceManager.inl"
#endif