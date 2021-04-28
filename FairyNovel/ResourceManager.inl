template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)		
{
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(filename))		// return false if fail to load
		throw std::runtime_error("ResourceManager::load = Failed to load " + filename);				

	auto inserted = nResourceMap.insert(std::make_pair(id, std::move(resource)));				
	assert(inserted.second);		
}


// accessing the texture, returning the memory address
template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	auto found = nResourceMap.find(id);			
	assert(found != nResourceMap.end());		

	return *found->second;						
}

// if we only have a pointer to the const TextureHolder
template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = nResourceMap.find(id);		
	assert(found != nResourceMap.end());		

	return *found->second;						
}


// load method for sf classes that takes extra parameter/s, eg. sf::shader
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();
	if (!resource->loadFromFile(filename, secondParam))		
		throw std::runtime_error("ResourceManager::load = Failed to load " + filename);

	auto inserted = nResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}


