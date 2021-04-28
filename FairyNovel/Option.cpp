#include "Option.hpp"

Option::Option() :
	value("")
{
}

Option::Option(const std::string& val) :
	value(val)
{
}

Option::operator int() const
{
	return std::stoi(value);
}

Option::operator std::string() const
{
	return value;
}