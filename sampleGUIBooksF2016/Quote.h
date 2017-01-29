#pragma once
#include"Author.h"
class Quote
{
public:
	Quote();
	Quote(std::string, std::string, Author); //accepts quote then theme then author's info
	void copy(Quote);
	std::string fullDisplay() const;
	std::string returnQuote();
	std::string returnYear();
	std::string returnTheme();
	std::string returnQuoteName();
	
private:
	std::string _quote, _theme;
	Author _authorInfo;
};