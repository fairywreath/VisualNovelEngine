#include "Utility.hpp"


#define PI 3.141592653589793238462643383f

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::string trim(const std::string& str)
{
	if (str.empty())
		return "";

	size_t i = 0; 
	size_t j = str.size() - 1;

	while (i < j && str[i] == ' ')
		i++;

	while (j > i && str[j] == ' ')
		j--;

	return str.substr(i, (size_t)j - i + 1);
}

bool checkEnds(std::string& str, char lhs, char rhs)
{
	if (str.empty()) return true;

	if (str[0] == lhs && str[str.size() - 1] == rhs) {
		str = trimEnds(str);
		return true;
	}
	return false;
}

std::string trimEnds(const std::string& str)
{
	if (str.size() <= 3) return "";
	return str.substr(1, str.size() - 2);
}

sf::String wrapText(sf::String string, unsigned width, const sf::Font& font, unsigned characterSize, unsigned extraLen, bool bold)
{
	unsigned currentOffset = 0;
	bool firstWord = true;
	std::size_t wordStart = 0;

	for (std::size_t pos = 0; pos < string.getSize(); pos++) {
		auto currentChar = string[pos];
		if (currentChar == '\n') {
			currentOffset = 0;
			firstWord = true;
			continue;
		}
		else if (currentChar == ' ') {
			wordStart = pos;
			firstWord = false;
		}

		auto& glyph = font.getGlyph(currentChar, characterSize, bold);
		currentOffset += static_cast<unsigned>(glyph.advance);

		if (!firstWord && currentOffset > width) {
			pos = wordStart;
			string[pos] = '\n';
			firstWord = true;
			currentOffset = 0;
		}
	}

	// for rest of the word
	for (unsigned int i = 0; i < extraLen; i++) {
		auto& glyph = font.getGlyph('a', characterSize, bold);
		currentOffset += static_cast<unsigned>(glyph.advance);
	}

	if (!firstWord && currentOffset > width) {
		string[wordStart] = '\n';
	}

	return string;
}

sf::Color parseColor(std::string str)
{
	return sf::Color();
}


std::string toString(sf::Keyboard::Key key)
{
#define KEYTOSTRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

	switch (key)
	{
		KEYTOSTRING_CASE(Unknown)
			KEYTOSTRING_CASE(A)
			KEYTOSTRING_CASE(B)
			KEYTOSTRING_CASE(C)
			KEYTOSTRING_CASE(D)
			KEYTOSTRING_CASE(E)
			KEYTOSTRING_CASE(F)
			KEYTOSTRING_CASE(G)
			KEYTOSTRING_CASE(H)
			KEYTOSTRING_CASE(I)
			KEYTOSTRING_CASE(J)
			KEYTOSTRING_CASE(K)
			KEYTOSTRING_CASE(L)
			KEYTOSTRING_CASE(M)
			KEYTOSTRING_CASE(N)
			KEYTOSTRING_CASE(O)
			KEYTOSTRING_CASE(P)
			KEYTOSTRING_CASE(Q)
			KEYTOSTRING_CASE(R)
			KEYTOSTRING_CASE(S)
			KEYTOSTRING_CASE(T)
			KEYTOSTRING_CASE(U)
			KEYTOSTRING_CASE(V)
			KEYTOSTRING_CASE(W)
			KEYTOSTRING_CASE(X)
			KEYTOSTRING_CASE(Y)
			KEYTOSTRING_CASE(Z)
			KEYTOSTRING_CASE(Num0)
			KEYTOSTRING_CASE(Num1)
			KEYTOSTRING_CASE(Num2)
			KEYTOSTRING_CASE(Num3)
			KEYTOSTRING_CASE(Num4)
			KEYTOSTRING_CASE(Num5)
			KEYTOSTRING_CASE(Num6)
			KEYTOSTRING_CASE(Num7)
			KEYTOSTRING_CASE(Num8)
			KEYTOSTRING_CASE(Num9)
			KEYTOSTRING_CASE(Escape)
			KEYTOSTRING_CASE(LControl)
			KEYTOSTRING_CASE(LShift)
			KEYTOSTRING_CASE(LAlt)
			KEYTOSTRING_CASE(LSystem)
			KEYTOSTRING_CASE(RControl)
			KEYTOSTRING_CASE(RShift)
			KEYTOSTRING_CASE(RAlt)
			KEYTOSTRING_CASE(RSystem)
			KEYTOSTRING_CASE(Menu)
			KEYTOSTRING_CASE(LBracket)
			KEYTOSTRING_CASE(RBracket)
			KEYTOSTRING_CASE(SemiColon)
			KEYTOSTRING_CASE(Comma)
			KEYTOSTRING_CASE(Period)
			KEYTOSTRING_CASE(Quote)
			KEYTOSTRING_CASE(Slash)
			KEYTOSTRING_CASE(BackSlash)
			KEYTOSTRING_CASE(Tilde)
			KEYTOSTRING_CASE(Equal)
			KEYTOSTRING_CASE(Dash)
			KEYTOSTRING_CASE(Space)
			KEYTOSTRING_CASE(Return)
			KEYTOSTRING_CASE(BackSpace)
			KEYTOSTRING_CASE(Tab)
			KEYTOSTRING_CASE(PageUp)
			KEYTOSTRING_CASE(PageDown)
			KEYTOSTRING_CASE(End)
			KEYTOSTRING_CASE(Home)
			KEYTOSTRING_CASE(Insert)
			KEYTOSTRING_CASE(Delete)
			KEYTOSTRING_CASE(Add)
			KEYTOSTRING_CASE(Subtract)
			KEYTOSTRING_CASE(Multiply)
			KEYTOSTRING_CASE(Divide)
			KEYTOSTRING_CASE(Left)
			KEYTOSTRING_CASE(Right)
			KEYTOSTRING_CASE(Up)
			KEYTOSTRING_CASE(Down)
			KEYTOSTRING_CASE(Numpad0)
			KEYTOSTRING_CASE(Numpad1)
			KEYTOSTRING_CASE(Numpad2)
			KEYTOSTRING_CASE(Numpad3)
			KEYTOSTRING_CASE(Numpad4)
			KEYTOSTRING_CASE(Numpad5)
			KEYTOSTRING_CASE(Numpad6)
			KEYTOSTRING_CASE(Numpad7)
			KEYTOSTRING_CASE(Numpad8)
			KEYTOSTRING_CASE(Numpad9)
			KEYTOSTRING_CASE(F1)
			KEYTOSTRING_CASE(F2)
			KEYTOSTRING_CASE(F3)
			KEYTOSTRING_CASE(F4)
			KEYTOSTRING_CASE(F5)
			KEYTOSTRING_CASE(F6)
			KEYTOSTRING_CASE(F7)
			KEYTOSTRING_CASE(F8)
			KEYTOSTRING_CASE(F9)
			KEYTOSTRING_CASE(F10)
			KEYTOSTRING_CASE(F11)
			KEYTOSTRING_CASE(F12)
			KEYTOSTRING_CASE(F13)
			KEYTOSTRING_CASE(F14)
			KEYTOSTRING_CASE(F15)
			KEYTOSTRING_CASE(Pause)
	}

	return "";
}

