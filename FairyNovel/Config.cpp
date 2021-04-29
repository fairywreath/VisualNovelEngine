#include "Config.hpp"

Config::Config() :
	nFilePath("")
{
}

Config::~Config()
{
	if (nFileStream.is_open()) {
		nFileStream.close();
	}
}

void Config::setPath(const std::string& path)
{
	nFilePath = path;
}

void Config::parse()
{
	startStream();
	nOptions.clear();

	std::string line = "";
	while (std::getline(nFileStream, line)) {
		size_t pos = line.find("=");
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		if (key.empty() || value.empty()) {
			continue;
		}
		nOptions[key] = Option(value);
	}
}

Option Config::getOption(const std::string& key) const
{
	if (nOptions.find(key) == std::end(nOptions)) {
		throw std::exception("No option with that key");
	}
	return nOptions.at(key);
}

void Config::startStream()
{
	if (!nFileStream.is_open()) {
		nFileStream.open(nFilePath.c_str());
		if (!nFileStream.good()) {
			nFileStream.clear();		// clear error state, basic guarantee
			throw std::exception("Config file does not exist / cannot be opened");
		}
	}
}
