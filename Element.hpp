#ifndef ELEMENT_HPP_GUARD
#define ELEMENT_HPP_GUARD

#include <iostream>
#include <string>

static const std::string emptyString = "";

class Element
{
private:
	std::string name;
	double atomicMass;
	std::string combustedStateSpecies;
	std::string deadStateSpecies;
	double ambientConc;

public:
	// Constructors
	Element()
		: name(emptyString) { }
	explicit Element(std::istream& is) 
		: name(emptyString) { read(is);}				// Construct an Element by reading its data from the gsi file

	void read(std::istream& is);						// Read data from the gsi file
	std::string Name() const { return name; }
	double AtomicMass() const { return atomicMass; }
	friend std::ostream& operator<<(std::ostream& os, const Element& elem);

	bool operator<(const Element& rhs) const			// Necessary to create a map<Element, int> in class Species
		{ return atomicMass < rhs.atomicMass; }
};

#endif // ELEMENT_HPP_GUARD