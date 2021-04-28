template <typename Type>
std::string toString(const Type& value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}