#ifndef ELEMENT_HPP_GUARD
#define ELEMENT_HPP_GUARD

#include "GS_Globals.hpp"

namespace BetterGS
{
	class GS_Element
	{
	private:
		std::string name;
		double atomicMass;
		std::string combustedStateSpecies;
		std::string deadStateSpecies;
		double ambientConc;

	public:
		// Constructors
		GS_Element()
			: name(emptyString) { }
		explicit GS_Element(std::istream& is)
			: name(emptyString) { read(is);}				// Construct an Element by reading its data from the gsi file

		// Input-output
		void read(std::istream& is);						// Read data from the gsi file
		friend std::ostream& operator<<(std::ostream& os, const GS_Element& elem);

		// Read-only properties
		std::string Name() const { return name; }
		double AtomicMass() const { return atomicMass; }
		std::string CombustedStateSpecies() const { return combustedStateSpecies; }
		std::string DeadStateSpecies() const { return deadStateSpecies; }
		double AmbientConc() const { return ambientConc; }

		// Operators
		bool operator<(const GS_Element& rhs) const			// Necessary to create a map<Element, int> in class Species
		{ return atomicMass < rhs.atomicMass; }
	};
}

#endif // ELEMENT_HPP_GUARD
