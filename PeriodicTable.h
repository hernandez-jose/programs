#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include <set>
#include <list>

#include "Element.h"

class PeriodicTable
{
public:
	PeriodicTable();
	virtual ~PeriodicTable();

	void printV();

	bool phraseInput(std::string);           // phrases the input of the user and add elements to link list
	std::list<Element> getInput();


protected:

private:
	std::set<Element> table;             // binary search tree
	std::list<Element> formula;         // link list
	int getNumber(char);
	bool ifNum(char);
};
