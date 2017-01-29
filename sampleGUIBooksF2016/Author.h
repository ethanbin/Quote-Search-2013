#pragma once
#include<string>
#include<iostream>
class Author
{
public:
	Author();
	Author(std::string, std::string, std::string);
	void copy(Author);
	std::string Author::year();
	std::string toString() const; // returns name and years as 1 string
	std::string returnName();
private:
	std::string _name, _birthyear, _deathyear;  // if a year is unknown, input 0
};