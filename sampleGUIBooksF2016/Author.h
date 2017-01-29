#pragma once
#include<string>
#include<iostream>
class Author
{
public:
	//default constructor - fills _name, _birthyear, and _deathyear as 0
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
	std::string _name, _birthyear, _deathyear;
};