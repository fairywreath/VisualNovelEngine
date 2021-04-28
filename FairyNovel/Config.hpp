#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "option.hpp"

#include <fstream>
#include <map>

class Config {
public:
	Config();
	~Config();
	void setPath(const std::string& path);
	void parse();
	Option getOption(const std::string& key) const;


private:
	std::string nFilePath;
	std::ifstream nFileStream;
	std::map<std::string, Option> nOptions;		

	void startStream();
};

#endif

