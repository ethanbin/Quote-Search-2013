#pragma once
#include"Author.h"
class Quote
{
public:
	//defaults to "0" for every variable
	Quote();

	//constructor taking string quote, string theme, and Author authorInfo
	Quote(std::string, std::string, Author);

	//constructor taking string quote and string theme for the Quote, and string name, string birthyear, and string deathyear for the Author in Quote
	Quote(std::string, std::string, std::string, std::string, std::string);

	//copy constructor
	void copy(Quote);

	//returns string formatted for display to user
	std::string fullDisplay() const;

	//returns _quote
	std::string returnQuote();

	//returns _year from _authorInfo
	std::string returnYear();

	//returns _theme
	std::string returnTheme();

	//returns _author from _authorInfo
	std::string returnQuoteName();
	
private:
	std::string _quote, _theme;
	Author _authorInfo;
};