#include "LewisStructure.h"



LewisStructure::LewisStructure()
{
	molarMass = 0;
	graph = NULL;
	lonePare = NULL;
}


LewisStructure::~LewisStructure()
{
	// deallocate memory
	if (graph != NULL)
		delete[] graph;

	if (lonePare != NULL)
		delete[] lonePare;
}

void LewisStructure::setFormula(std::list<Element> form)
{
	formula = form;
	numAtom = form.size();
	numValence = 0;

	// get number of valance electrons from group number
	for (auto it = form.begin(); it != form.end(); ++it)
	{
		// total number of valance electrons
		if (it->get_group() > 10)
			numValence = (it->get_group() - 10) + numValence;
		else
			numValence = (it->get_group()) + numValence;

		// molar mass
		molarMass += it->get_mass();
	}

	graph = new int[numAtom*3];
	lonePare = new int[numAtom];

	for (int i = 0; i < numAtom * 3; i++)
	{
		graph[i] = 0;
	}
}

Element LewisStructure::leastElectroneg(std::list<Element> inFormula)
{
	int groupLowNum = 18, periodHighNum = 0, periodCount[7];

	// look for least electronegative atom as central exclude C and H

	// find atom with hiest period
	for (auto it = inFormula.begin(); it != inFormula.end(); ++it)
	{
		if (it->get_period() >= periodHighNum)
		{
			periodCount[it->get_period() - 1]++; // count the number of elements with same period
			periodHighNum = it->get_period();
		}
	}

	// insert all elements in the smae period to vector
	std::vector<Element> samePeriodElements;

	// go back and look for items
	for (auto it = inFormula.begin(); it != inFormula.end(); ++it)
	{
		if (periodHighNum == it->get_period()) // store all elements with same period number
			samePeriodElements.push_back(*it);
	}

	// check if two or more elements are in the same period
	if (samePeriodElements.size() >= 2)
	{
		// resolve central atom
		for (auto it = samePeriodElements.begin(); it != samePeriodElements.end(); ++it)
		{
			if (it->get_group() < groupLowNum)
					groupLowNum = it->get_group();
		}

		// get lowest group number
		for (auto it = samePeriodElements.begin(); it != samePeriodElements.end(); ++it)
		{
			if (groupLowNum == it->get_group())
				return *it;
		}
	}
	else
	{
		// only one element in "samePeriodElements" so first item is central atom
		return samePeriodElements.front();
	}
}

void LewisStructure::outputStructure()
{
	Element ca = leastElectroneg(formula);

	// if carbon thats central atom
	for (auto it = formula.begin(); it != formula.end(); ++it)
	{
		if (it->get_symbol() == "C")
		{
			ca = *it;
			break;
		}
			
	}
	//std::cout << "Central atom: " << ca.get_symbol() << "\n";

	/* 
		remove central element from formula
		sometimes least electronegative atom would not work so find central atom by
		the element that is unique
	*/
	
	int* counts = new int[numAtom];
	int ind = 0; // index of *counts
	// set to zero
	for (int i = 0; i < numAtom; i++) counts[i] = 0;

	// count number of time an element appears
	for (auto it = formula.begin(); it != formula.end(); ++it)
	{
		// count cetral atoms occurence
		for (auto its = formula.begin(); its != formula.end(); ++its)
		{
			if (it != its) // if not the same atom
			{
				if(*it == *its) // if the same type of element
					counts[ind]++;
			}
		}
		//if(ca == *it)
		//std::cout << it->get_symbol() << "\n";
		ind++;
	}

	//for (int i = 0; i < numAtom; i++) std::cout << "counts[" << i << "] = " << counts[i] << "\n";

	ind = 0;
	bool check = false; 

	// check if central atom not unque -- change central atom
	for (auto it = formula.begin(); it != formula.end(); ++it)
	{
		if ((ca == *it) && (counts[ind] >= 1)) // central atom not unique
			check = true;

		if (check == true)
		{
			// not unique -- get least occurance
			// go back from begining of formula
			int inds = 0;
			for (auto it1 = formula.begin(); it1 != formula.end(); ++it1)
			{
				if (counts[inds] == 0)
				{
					ca = *it1;
					//std::cout << it1->get_symbol() << " -- \n";
					break;
				}
				inds++;
			}
			break;
		}

		ind++;
	}

	formula.remove(ca);
	delete[] counts;

	/*
		now "formula" is outer atoms and "ca" central atom
		2D array 3x(number of outer atoms) row by col
		row 0: first element is central atom, then the rest are outer atoms.
				This represents the number of bonds to the element
		row 1: number of non-bonding electrons
		row 2: number of valance electrons
	*/

	// Note access to 2D array formula -- x + (col * y) -- with index starting at zero
	int outerAtom = formula.size();
	//std::cout << "outerAtom = " << outerAtom << "\n";

	numValence = numValence - (outerAtom * 2); // one bond to each outer atom
	//std::cout << "numValence = " << numValence << "\n";

	int x=1, ve;

	// give the rest of valance electrons to outer atoms
	for (auto it = formula.begin(); it != formula.end(); ++it)
	{
		// outer atom bond to central atom
		graph[x + (numAtom * 0)] = 1;
		//std::cout << "garph[" << x + (numAtom * 0) << "]\n";

		// assign valance electrons
		if (it->get_symbol() != "H")
		{
			if (numValence >= 6)
			{
				graph[x + (numAtom * 1)] = 6; // assign 6 valance electrons
				numValence = numValence - 6; // keep trac of total valance electrons
				//std::cout << numValence << " " << it->get_symbol() << "\n";
			}
			else
			{
				graph[x + (numAtom * 1)] = numValence; // assign remaining electrons
				numValence = 0;
			}
			
		}
		else
		{
			graph[x + (numAtom * 1)] = 0;
			//std::cout << "garph[" << x + (numAtom * 1) << "] = 0\n";
		}

		if (it->get_group() >= 10)
			ve = it->get_group() - 10;
		else
			ve = it->get_group();

		graph[x + (numAtom * 2)] = ve;
		x++;
	}

	// central atom bonds
	for (int i = 1; i <= outerAtom; i++)
	{
		graph[0] += graph[i + numAtom*0];
	}

	// assign remainding valance electrons to central atom
	if (numValence > 0)
	{
		graph[0 + (numAtom * 1)] = numValence;
		numValence = 0;
	}

	if (ca.get_group() >= 10)
		ve = ca.get_group() - 10;
	else
		ve = ca.get_group();

	graph[0 + (numAtom * 2)] = ve;
	//

	// apply formal charge
	formalCharge();

	/*  //display matrix
	for (int i = 0; i < 3; ++i)
	{
		for (int x = 0; x < numAtom; x++)
		{
			std::cout << graph[x + i*numAtom] << " ";
		}
		std::cout << std::endl;
	}*/


	// output meta data
	std::cout << "AX" << outerAtom;
	int E = graph[0 + (numAtom * 1)] / 2;
	if (E > 0)
		std::cout << "E" << E << std::endl;
	else
		std::cout << std::endl;

	for (int x = 0; x < numAtom; x++)
	{
		std::cout << graph[x];
		if ((x + 1) < numAtom)
			std::cout << " ";
	}

	std::cout << std::endl << molarMass << std::endl;

	std::cout << ca.get_symbol() << " ";
	for (auto it = formula.begin(); it != formula.end(); ++it)
	{
		std::cout << it->get_symbol();
		++it;
		if (it != formula.end())
			std::cout << " ";
		--it;
	}

}


void LewisStructure::formalCharge()
{
	int bonds;

	// while central atom formal charge is not zero
	if (calcFC(0) != 0)
	{
		// find amount of bonds to make zero charge
		bonds = graph[0 + numAtom * 2] - graph[0 + numAtom * 1];
		if (bonds > graph[0])
		{
			int diff = bonds - graph[0]; // number of bonds to hand out
			int x = 1; // index
			for (auto it = formula.begin(); it != formula.end(); ++it) // formula is outer atoms
			{
				if (it->get_symbol() != "H")
				{
					if ((diff != 0) && (graph[x + numAtom * 1] >= 2))
					{
						graph[x + numAtom * 1] -= 2;
						graph[x + numAtom * 0]++;
						graph[0]++;
						diff--;
					}
				}
				x++;
			}
			
			// finish filling last element
			while (diff != 0)
			{
				graph[(numAtom-1) + numAtom * 1] -= 2;
				graph[(numAtom - 1) + numAtom * 0]++;
				graph[0]++;
				diff--;
			}
		}

	}
}

int LewisStructure::calcFC(int col)
{
	int numBonds, nonBondedE, numValanceE;

	numBonds = graph[col + numAtom*0];
	nonBondedE = graph[col + numAtom*1];
	numValanceE = graph[col + numAtom*2];

	return (numValanceE - nonBondedE - numBonds); // formal charge formula
}
