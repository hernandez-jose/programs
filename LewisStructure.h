#pragma once

#include <iostream>
#include <list>
#include <vector>
#include "Element.h"

class LewisStructure
{
public:
	LewisStructure();
	~LewisStructure();

	void setFormula(std::list<Element>);
	void outputStructure();


private:
	Element leastElectroneg(std::list<Element>);
	void formalCharge();
	int calcFC(int); // calculate formal charge

	std::list<Element> formula; // formula to process -- user input
	int numAtom;
	int numValence;
	double molarMass;
	int* graph;	// represents number of bonds
	int* lonePare;
};

