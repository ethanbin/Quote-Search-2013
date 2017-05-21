#pragma once
#include<vector>
#include"Quote.h"

class Quotes
{
public:
	Quotes();
	Quotes(const Quotes &);
	Quotes& operator = (const Quotes &);
	~Quotes();

	void resize(int);
	void authorSelectionSort();
	void themeSelectionSort();
	
	//enters a Quote into _Quotes[i] and returns true if i is within the array. Otherwise, just returns false
	bool entry(Quote, int);
	int authorBinarySearch(std::string);
	int themeBinarySearch(std::string);
	std::string returnFullQuote(int);
	std::string displayAll();
	std::string searchAuthor(std::string);
	std::string searchQuote(std::string);
	std::string searchTheme(std::string);
	std::string searchYear(std::string);
	void addQuote(std::string, std::string, std::string, std::string, std::string, std::string);

private:
	int _NumQuotes;
	//std::vector<Quote> _Quotes;
	Quote *_Quotes;
	int _NumPasses = 0;
};