#pragma once
#include"Author.h"

Author::Author() :_name("0"), _birthyear("0"), _deathyear("0"){}

Author::Author(std::string name, std::string birth, std::string death)
{
	_name = name;
	_birthyear = birth;
	_deathyear = death;
}

void Author::copy(Author copying)
{
	_name = copying._name;
	_birthyear = copying._birthyear;
	_deathyear = copying._deathyear;
}

std::string Author::year()
{
	return _birthyear + " " + _deathyear;
}

std::string Author::toString()const
{
	if (_birthyear == "0" && _deathyear=="0")
		return _name + " N/A - N/A"; //returns like “Billy Bob, N/A - N/A”

	else if (_birthyear == "0")
		return _name + " N/A - " + _deathyear; //returns like “Billy Bob, N/A - 1990”

	else if (_deathyear == "0")
		return _name + " " + _birthyear + " - N/A"; //returns like “Billy Bob, 1900 - N/A”
	
	else
		return _name + " " + _birthyear + " - " + _deathyear; //returns like “Billy Bob, 1900-1990”
}

std::string Author::returnName()
{
	return _name;
}