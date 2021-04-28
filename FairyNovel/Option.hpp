#ifndef OPTION_HPP
#define OPTION_HPP

#include <string>

class Option {
public:
	Option();
	explicit Option(const std::string& val);
	operator int() const;			// return value as int
	operator std::string() const;

private:
	std::string value;

};



#endif