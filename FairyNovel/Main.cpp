#include "Application.hpp"

#include <iostream>

int main()
{
	try
	{
		Application app("config.cfg");
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}
