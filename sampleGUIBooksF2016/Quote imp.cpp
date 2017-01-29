#pragma once
#include"Quote.h"
Quote::Quote(std::string quoteLine, std::string theme, Author authorInfo)
{
	_quote = quoteLine;
	_theme = theme;
	_authorInfo.copy(authorInfo);
}

void Quote::copy(Quote quoteCopying)
{
	_quote = quoteCopying._quote;
	_theme = quoteCopying._theme;
	_authorInfo.copy(quoteCopying._authorInfo);
}

std::string Quote::fullDisplay()const
{
	std::string capTheme = _theme;
	capTheme[0] = toupper(capTheme[0]);	//purely superficial 
	if (_quote == "0")
		return "\0";
	else
	{
		std::string output = _quote + "\n\t" + capTheme + "\n\t" + _authorInfo.toString() + "\n\n";
		return output;
	}
}

std::string Quote::returnQuote()
{
	return _quote;
}

std::string Quote::returnYear()
{
	std::string year=_authorInfo.year();
	return year;
}

std::string Quote::returnTheme()
{
	return _theme;
}

std::string Quote::returnQuoteName()
{
	std::string name = _authorInfo.returnName();
	return name;
}

Quote::Quote() :_quote("0"), _theme("0"), _authorInfo("0","0","0"){}