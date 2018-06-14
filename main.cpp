/*
Created By: Jose Hernandez Naranjo
*/

#include<iostream>
#include<list>
#include <cstddef>
#include <stdio.h>

#include "PeriodicTable.h"
#include "LewisStructure.h"	// represent structure using graphs
#include "Element.h"

using namespace std;


int main(int argc, char *argv[])
//int main()
{
	PeriodicTable pt;
	string phrase(argv[1]);
	//string phrase = "C2O4";

	pt.phraseInput(phrase);
	list<Element> formulas;
	formulas = pt.getInput();
	 
	LewisStructure struc;

	struc.setFormula(formulas);

	struc.outputStructure();

	return 0;
}
