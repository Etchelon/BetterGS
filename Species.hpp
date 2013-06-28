#ifndef SPECIES_HPP_GUARD
#define SPECIES_HPP_GUARD

#include "Element.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>

struct NASA_Coefficients
{
	double lowerBound;
	double upperBound;
	std::array<double, 9> coefficients;

	void print(std::ostream& os) const;
};

class Species
{
private:
	// Physical and TD properties
	std::string formula;
	std::string name;
	unsigned int phase;
	double density;
	double dH0f;
	double dS0f;
	double Tc;
	double Pc;
	double MW;
	std::map<Element, int> elements;

	// NASA polynomials coefficients
	unsigned int nIntervals;
	std::vector<NASA_Coefficients> nasa;

public:
	Species() : formula(emptyString) { }
	explicit Species(std::istream& is, const std::vector<Element>& elem);

	void read(std::istream& is);
	double compute_MW() const { return MW; }
	friend std::ostream& operator<<(std::ostream& os, const Species& species);
};

#endif // SPECIES_HPP_GUARD