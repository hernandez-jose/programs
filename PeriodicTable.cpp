#include "PeriodicTable.h"

PeriodicTable::PeriodicTable()
{
	// load periodic table data
	std::ifstream pt("pt.txt");
	std::string line, sym, name, group, period, mass, eleNum;
	int group1, period1, eleNum1;
	double mass1;
	Element atom;

	if (pt.is_open())
	{
		while (!pt.eof())
		{
			std::getline(pt, eleNum, '\t');
			pt >> sym >> group >> period >> name >> mass;

			group1 = std::stoi(group);
			period1 = std::stoi(period);
			eleNum1 = std::stoi(eleNum);
			mass1 = std::stod(mass);

			// add elements to periodic table
			atom.set_symbol(sym);
			atom.set_name(name);
			atom.set_elementNumber(eleNum1);
			atom.set_group(group1);
			atom.set_mass(mass1);
			atom.set_period(period1);

			table.insert(atom);

			getline(pt, line);
		}
	}
	pt.close();

}

PeriodicTable::~PeriodicTable()
{
	//dtor
}

void PeriodicTable::printV()
{
	for (auto it = formula.begin(); it != formula.end(); ++it)
	{
		std::cout << *it << " ";
	}
}

bool PeriodicTable::phraseInput(std::string input)
{
	Element atom; // used for searching for elements -- a blank object

	// loop through the input
	for (unsigned int i = 0; i<input.length(); ++i)
	{
		// get two letters
		std::string dummyString;
		dummyString += input[i];
		dummyString += input[i+1];

		//std::cout << dummyString;

		atom.set_symbol(dummyString);
		auto data = table.find(atom); // search periodic table

		// if no match with two letters search with one letter
		if (table.count(atom) == 0)
		{
			std::string tempS;
			tempS += dummyString[0];
			atom.set_symbol(tempS);
			data = table.find(atom); // search periodic table

			// if nothing found wrong input
			if (table.count(atom) == 0)
				return false;
				//std::cout << "false ";
				

			int num = getNumber(input[i + 1]); // convert input string to int

			if (ifNum(input[i + 1])) // skip reading the number from input
				i++;

			for (int y = 0; y<num; y++) // subscript of formula now becomes amount of elements
				formula.push_back(*data);  // add to link list
		}
		else
		{
			// element is two letters here

			int num = getNumber(input[i + 2]);

			if (ifNum(input[i + 2])) // skip reading the number from input
				i = i + 2; // move three boxes
			else
				i++;

			for (int y = 0; y<num; y++) // subscript of formula now becomes amount of elements
				formula.push_back(*data);  // add to link list

		}
	} // close for loop

	//std::cout << "true ";
	return true;
}

bool PeriodicTable::ifNum(char num)
{
	if (num == '1')
		return true;
	else if (num == '2')
		return true;
	else if (num == '3')
		return true;
	else if (num == '4')
		return true;
	else if (num == '5')
		return true;
	else if (num == '6')
		return true;
	else if (num == '7')
		return true;
	else if (num == '8')
		return true;
	else if (num == '9')
		return true;

	return false; // if its a letter
}

int PeriodicTable::getNumber(char num)
{
	if (num == '1')
		return 1;
	else if (num == '2')
		return 2;
	else if (num == '3')
		return 3;
	else if (num == '4')
		return 4;
	else if (num == '5')
		return 5;
	else if (num == '6')
		return 6;
	else if (num == '7')
		return 7;
	else if (num == '8')
		return 8;
	else if (num == '9')
		return 9;

	return 1; // if its a letter or something else
}

std::list<Element> PeriodicTable::getInput()
{
	return formula;
}
