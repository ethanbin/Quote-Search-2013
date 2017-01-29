#pragma once
#include<string>
#include<iostream>
class Author
{
public:
	Author();

	//copy constructor
	void copy(Author);

	//constructor accepting name, birthyear, and deathyear
	Author(std::string, std::string, std::string);	

	//returns "birthyear deathyear"
	std::string Author::year();

	//returns "name, birthyear - deathyear"
	std::string toString() const; 

	//returns "name"
	std::string returnName();
private:
	std::string _name, _birthyear, _deathyear;  // if a year is unknown, input 0
};