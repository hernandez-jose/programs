#pragma once

#include<string>

class Element
{
public:
	Element();
	Element(std::string, std::string, int, int, int, double);
	virtual ~Element();

	// setters
	void set_symbol(std::string);
	void set_name(std::string);
	void set_elementNumber(int);
	void set_period(int);
	void set_group(int);
	void set_mass(double);

	// getters
	std::string get_symbol() const;
	std::string get_name() const;
	int get_elementNumber() const;
	int get_period() const;
	int get_group() const;
	double get_mass() const;

	friend bool operator>(const Element&, const Element&);
	friend bool operator<(const Element&, const Element&);
	friend bool operator==(const Element&, const Element&);
	friend bool operator!=(const Element&, const Element&);
	friend std::ostream& operator<<(std::ostream&, const Element&);


protected:

private:
	std::string symbol;
	std::string name;
	int elementNumber;
	int period;
	int group;
	double mass;
};

