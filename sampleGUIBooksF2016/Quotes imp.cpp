#pragma once
#include<string>
#include <fstream>
#include "Quotes.h"
#include <windows.h>
#include <stdio.h>
#include <shellapi.h>
#include <stdlib.h>

Quotes::Quotes()
{
	_NumQuotes = 0;
	_Quotes = '\0';
	_NumPasses = 0;
}

Quotes::Quotes(const Quotes & copyFrom)
{
	_NumQuotes = copyFrom._NumQuotes;
	_Quotes = new Quote[_NumQuotes];
	for (int i = 0; i < _NumQuotes; i++)
		_Quotes[i] = copyFrom._Quotes[i];
}

void Quotes::operator = (const Quotes & copyFrom)
{
	_NumQuotes = copyFrom._NumQuotes;
	_Quotes = new Quote[_NumQuotes];
	for (int i = 0; i < _NumQuotes; i++)
		_Quotes[i] = copyFrom._Quotes[i];
}

Quotes::~Quotes()
{
	//_Quotes = '\0';
	delete[] _Quotes;
}

void Quotes::resize(int numHowMany)
{
	_NumQuotes = numHowMany;
	_Quotes = new Quote[_NumQuotes];
}

void Quotes::authorSelectionSort()
{
	int smallestIndex, location;
	Quote temp;
	for (int i = 0; i < _NumQuotes; i++)
	{
		smallestIndex = i;
		for (location = i + 1; location < _NumQuotes; location++)
		{
			if (_Quotes[location].returnQuoteName() <= _Quotes[smallestIndex].returnQuoteName())
				smallestIndex = location;
		}
		temp = _Quotes[smallestIndex];
		_Quotes[smallestIndex] = _Quotes[i];
		_Quotes[i] = temp;
	}
}

void Quotes::themeSelectionSort()
{
	int smallestIndex, location;
	Quote temp;
	for (int i = 0; i < _NumQuotes; i++)
	{
		smallestIndex = i;
		for (location = i + 1; location < _NumQuotes; location++)
		{
			if (_Quotes[location].returnTheme() <= _Quotes[smallestIndex].returnTheme())
				smallestIndex = location;
		}
		temp = _Quotes[smallestIndex];
		_Quotes[smallestIndex] = _Quotes[i];
		_Quotes[i] = temp;
	}
}

void Quotes::entry(Quote toAdd, int i)
{
	_Quotes[i].copy(toAdd);
}

int Quotes::authorBinarySearch(std::string userInput)
{
	void authorSelectionSort();
	std::string currentAuthor;
	int searchEnd = _NumQuotes-1;
	bool finalStep = false;
	int searchStart = 0;
	int searchMid = searchEnd / 2;
	while (searchStart <= searchEnd)
	{
		currentAuthor = _Quotes[searchMid].returnQuoteName();
		currentAuthor.pop_back(); // because all authors end with a ,
		_NumPasses++;

		if (currentAuthor == userInput)
			return searchMid;
		if (finalStep == true)
		{
			_NumPasses = 0;
			return -1;
		}
		else if (userInput > currentAuthor)
		{
			searchStart = searchMid;
			searchMid = (searchStart + (searchEnd - searchStart) / 2);
			if (searchMid == searchStart)
			{
				searchMid++;
				finalStep = true;
			}
		}
		else if (userInput < currentAuthor)
		{
			searchEnd = searchMid;
			searchMid = (searchEnd - (searchEnd - searchStart) / 2);
			if (searchMid == searchEnd)
			{
				searchMid--;
				finalStep = true;
			}
		}	
	}
}

int Quotes::themeBinarySearch(std::string userInput)
{
	userInput[0] = tolower(userInput[0]);
	std::string currentTheme;
	int searchEnd = _NumQuotes - 1;
	bool finalStep = false;
	int searchStart = 0;
	int searchMid = searchEnd / 2;
	while (searchStart <= searchEnd)
	{
		currentTheme = _Quotes[searchMid].returnTheme();
		_NumPasses++;

		if (currentTheme == userInput)
			return searchMid;

		if (finalStep == true)
		{
			_NumPasses = 0;
			return -1;
		}
		else if (userInput > currentTheme)
		{
			searchStart = searchMid;
			searchMid = (searchStart + (searchEnd - searchStart) / 2);
			if (searchMid == searchStart)
			{
				searchMid++;
				finalStep = true;
			}
		}
		else if (userInput < currentTheme)
		{
			searchEnd = searchMid;
			searchMid = (searchEnd - (searchEnd - searchStart) / 2);
			if (searchMid == searchEnd)
			{
				searchMid--;
				finalStep = true;
			}
		}
	}
}

std::string Quotes::returnFullQuote(int index)
{
	std::string numpasses = "Number of passes for this search: " + std::to_string(_NumPasses);
	_NumPasses = 0;
	return numpasses + "\n" + _Quotes[index].fullDisplay();
}

std::string Quotes::displayAll()
{
	std::string search = "\n";
	for (int i = 0; i<_NumQuotes ; i++)
		search = search + _Quotes[i].fullDisplay();
	return search;
}

std::string Quotes::searchAuthor(std::string userInput)
{
	std::string searchResults = "\n";

	//this code searches for a matching string within another string (like find) while preventing case-sensitivity
	bool stop = false;
	std::string line, upperUserInput=userInput;

	//the follwing code will, for every author, compare the letters of userInput to the letters of the author's name until a match is found
	//the author will hereby be known as "line"
	//to keep the code from being littered with notes, the following brief summary is numbered to indicate where each action is executed.

//1)	the first loop will turn userInput into all lowercase, then makes a copy of userInput called upperUserInput in all caps to remove case sensitivity when searching in (3)
//2)	the main loop will begin by setting i to 0 (so program will begin at the first letter of userInput) and will end when all of userInput has been checked
//3)	the code will check if the current letter of the user's input matches the current letter of line, whether its upper case or lower case
//4)	if a letter does not match after finding earlier matches, restart checking each letter of userInput while continuing where we left off at line
//5)	if userInput has beeen completely searched and nothing was found, move on to the next quote. 
//6)	if no quote had a single match, say "no results found"
//7)	if the entirety of userInput matches something in line, add quote info to searchResults, prevent 6 with anythingFound, and break the loop to move on
//8)	return the string containing all quotes with all their info
	
	for (int x = 0; x < userInput.length(); x++)
	{
		userInput[x] = tolower(userInput[x]);
		upperUserInput[x] = toupper(userInput[x]);
	}
	
	for (int q = 0; q < _NumQuotes ;q++)
		{
			//j, used to count what we are up to in line,  is intialized now to prevent it from being reset mid-search
			int lettersInARow = 0, j = 0; 
			line=_Quotes[q].returnQuoteName(); //call once and set line to it instead of repeatedly calling the function for efficiency
			for (int i = 0; i != userInput.length() + 1; i++)					//2
			{
				if (stop == true) //for 5
				{
					stop = false;
					break;
				}
				if (lettersInARow == userInput.length())						//7
				{
					searchResults = searchResults + _Quotes[q].fullDisplay();
					break;
				}
				for (; j < line.length(); j++)
				{
					if (userInput[i] == line[j] || upperUserInput[i] == line[j]) //3
					{
						lettersInARow++; //for 4
						j++; // because the break doesnt let the loop do j++ 
						break;
					}
					else if (userInput[i] != line[j] && lettersInARow > 0)		//4
					{
						i = -1; //i is about to get +1 from the first for loop, so this will counter that
						lettersInARow = 0;
						break;
					}
					else if (j == line.length())								//5
					{
						stop = true;
						break;
					}
				}
			}
		}
	if (searchResults == "\n")												//6
		return "0";
	else																	//8
		return searchResults+"\n";
}

std::string Quotes::searchTheme(std::string userInput)
{
	std::string searchResults = "\n";
	bool stop = false;
	std::string line, upperUserInput = userInput;

	//the follwing code will, for every author, compare the letters of userInput to the letters of the theme until a match is found
	//the theme will hereby be known as "line"
	//for more detailed notes, refer to corresponding numbered notes in searchAuthor

	for (int x = 0; x < userInput.length(); x++)
	{
		userInput[x] = tolower(userInput[x]);
		upperUserInput[x] = toupper(userInput[x]);
	}
		for (int q = 0; q < _NumQuotes; q++)
	{
		//j, used to count what we are up to in line,  is intialized now to prevent it from being reset mid-search
		int lettersInARow = 0, j = 0;
		line = _Quotes[q].returnTheme(); //call once and set line to it instead of repeatedly calling the function for efficiency
		for (int i = 0; i != userInput.length() + 1; i++)					//2
		{
			if (stop == true) //for 5
			{
				stop = false;
				break;
			}
			if (lettersInARow == userInput.length())						//7
			{
				searchResults = searchResults + _Quotes[q].fullDisplay();
				break;
			}
			for (; j < line.length(); j++)
			{
				if (userInput[i] == line[j] || upperUserInput[i] == line[j])//3
				{
					lettersInARow++; //for 4
					j++; // because the break doesnt let the loop do j++ 
					break;
				}
				else if (userInput[i] != line[j] && lettersInARow > 0)		//4
				{
					i = -1; //i is about to get +1 from the first for loop, so this will counter that
					lettersInARow = 0;
					break;
				}
					else if (j == line.length())							//5
				{
					stop = true;
					break;
				}
			}
		}
	}
	if (searchResults == "\n")												//6
		return "0";
	else
		return searchResults + "\n";										//8
}

std::string Quotes::searchQuote(std::string userInput)
{
	std::string searchResults = "\n";
	bool stop = false, anythingFound = false;
	std::string line, upperUserInput = userInput;

	//the follwing code will, for every quote, compare the letters of userInput to the letters of the quote until a match is found
	//the theme will hereby be known as "line"
	//for more detailed notes, refer to corresponding numbered notes in searchAuthor

	for (int x = 0; x < userInput.length(); x++)
	{
		userInput[x] = tolower(userInput[x]);
		upperUserInput[x] = toupper(userInput[x]);
	}
		for (int q = 0; q < _NumQuotes; q++)
	{
		//j, used to count what we are up to in line,  is intialized now to prevent it from being reset mid-search
		int lettersInARow = 0, j = 0;
		line = _Quotes[q].returnQuote(); //call once and set line to it instead of repeatedly calling the function for efficiency
		for (int i = 0; i != userInput.length() + 1; i++)					//2
		{
			if (stop == true) //for 5
			{
				stop = false;
				break;
			}
			if (lettersInARow == userInput.length())						//7
			{
				searchResults = searchResults + _Quotes[q].fullDisplay();
				break;
			}
			for (; j < line.length(); j++)
			{
				if (userInput[i] == line[j] || upperUserInput[i] == line[j])//3
				{
					lettersInARow++; //for 4
					j++; // because the break doesnt let the loop do j++ 
					break;
				}

				else if (userInput[i] != line[j] && lettersInARow > 0)		//4
				{
					i = -1; //i is about to get +1 from the first for loop, so this will counter that
					lettersInARow = 0;
					break;
				}
				else if (j == line.length())								//5
				{
					stop = true;
					break;
				}
			}
		}
	}
		if (searchResults == "\n")												//6
			return "0";
		else
			return searchResults+"\n";
}

std::string Quotes::searchYear(std::string userInput)
{
	std::string searchResults = "\n";
	bool stop = false, anythingFound = false;
	std::string line, upperUserInput = userInput;

	//the follwing code will, for every year, compare the numbers of userInput to the numbers of the quote until a match is found
	//the theme will hereby be known as "line"
	//for more detailed notes, refer to corresponding numbered notes in searchAuthor

	for (int q = 0; q < _NumQuotes; q++)
	{
		//j, used to count what we are up to in line,  is intialized now to prevent it from being reset mid-search
		int lettersInARow = 0, j = 0;
		line = _Quotes[q].returnYear(); //call once and set line to it instead of repeatedly calling the function for efficiency

		for (int i = 0; i != userInput.length() + 1; i++)					//2
		{
			if (stop == true) //for 5
			{
				stop = false;
				break;
			}
			if (lettersInARow == userInput.length())						//7
			{
				searchResults = searchResults + _Quotes[q].fullDisplay();
				break;
			}
			for (; j < line.length(); j++)
			{
				if (userInput[i] == line[j] || upperUserInput[i] == line[j])//3
				{
					lettersInARow++; //for 4
					j++; // because the break doesnt let the loop do j++ 
					break;
				}
				else if (userInput[i] != line[j] && lettersInARow > 0)		//4
				{
					i = -1; //i is about to get +1 from the first for loop, so this will counter that
					lettersInARow = 0;
					break;
				}
				else if (j == line.length())								//5
				{
					stop = true;
					break;
				}
			}
		}
	}
	if (searchResults == "\n")												//6
		return "0";
	else
		return searchResults+"\n";
}

void Quotes::addQuote(std::string quote, std::string theme, std::string author, std::string birth, std::string death, std::string argv1)
{
	Quote toAdd(quote, theme, author, birth, death);

	//create a new user made quote using NEW
	//this leaves them unsorted. whenever this is called it will require both sorting methods after.

	Quote *temp = _Quotes;
	_NumQuotes++;
	_Quotes = new Quote[_NumQuotes];
	for (int i = 0;i < _NumQuotes - 2; i++) //-1 because _NumQuotes is a size not index, another -1 because we dont want to try overwriting last address of _Quotes
		_Quotes[i] = temp[i];
	_Quotes[_NumQuotes-1].copy(toAdd);

	//rest hard-saves the user made quote into a text file
	std::ofstream userAddedQuotes;
	userAddedQuotes.open(argv1, std::ios::out | std::ios::app);
	userAddedQuotes << "\n" + quote + "\n";
	theme[0] = tolower(theme[0]);
	userAddedQuotes << theme + "\n";
	userAddedQuotes << author + " (" + birth + " - " + death + ")";
	userAddedQuotes.close();
	temp = '\0';
	delete temp;
}