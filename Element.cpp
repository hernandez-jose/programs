#include "Element.h"

Element::Element()
{
	//ctor
}

Element::Element(std::string symbol1, std::string name1, int elementNumber1, int period1, int group1, double mass1)
{
	symbol = symbol1;
	name = name1;
	elementNumber = elementNumber1;
	period = period1;
	group = group1;
	mass = mass1;
}

Element::~Element()
{
	//dtor
}

bool operator>(const Element& lhs, const Element& rhs) // for BST operation comparison
{
	return (lhs.get_symbol() > rhs.get_symbol());
}

bool operator<(const Element& lhs, const Element& rhs) // for BST operation comparison
{
	return (lhs.get_symbol() < rhs.get_symbol());
}

bool operator==(const Element& lhs, const Element& rhs)
{
	return (lhs.get_symbol() == rhs.get_symbol());
}

bool operator!=(const Element& lhs, const Element& rhs)
{
	return (lhs.get_symbol() != rhs.get_symbol());
}

std::ostream& operator<<(std::ostream& cOut, const Element& atom)
{
	cOut << atom.get_symbol();
	return cOut;
}

// setters
void Element::set_symbol(std::string data) { symbol = data; }
void Element::set_name(std::string data) { name = data; }
void Element::set_elementNumber(int data) { elementNumber = data; }
void Element::set_period(int data) { period = data; }
void Element::set_group(int data) { group = data; }
void Element::set_mass(double data) { mass = data; }

// getters
std::string Element::get_symbol() const { return symbol; }
std::string Element::get_name() const { return name; }
int Element::get_elementNumber() const { return elementNumber; }
int Element::get_period() const { return period; }
int Element::get_group() const { return group; }
double Element::get_mass() const { return mass; }
