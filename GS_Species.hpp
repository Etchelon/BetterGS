#ifndef SPECIES_HPP_GUARD
#define SPECIES_HPP_GUARD

#include "GS_Globals.hpp"
#include "GS_Element.hpp"

namespace BetterGS
{
	struct NASA_Coefficients
	{
		double lowerBound;
		double upperBound;
		std::array<double, 9> coefficients;

		void print(std::ostream& os) const;
	};

	class GS_Species
	{
	private:
		// Physical and TD properties
		std::string formula;
		std::string name;
		unsigned int phase;
		double density;
		double dH0f;
		double dS0f;
		double _Tc;
		double _Pc;
		double _MW;
		std::map<GS_Element, int> elements;

		// NASA polynomials coefficients
		unsigned int nIntervals;
		std::vector<NASA_Coefficients> nasa;

	public:
		// Constructors
		GS_Species() : formula(emptyString) { }
		explicit GS_Species(std::istream& is, const std::vector<GS_Element>& elem);

		// Input/output
		void read(std::istream& is);
		friend std::ostream& operator<<(std::ostream& os, const GS_Species& species);

		// Read-only properties
		std::string Formula() const { return formula; }
		std::string Name() const { return name; }
		unsigned int Phase() const { return phase; }
		double Density() const { return density; }
		double DH0f() const { return dH0f; }
		double DS0f() const { return dS0f; }
		double Tc() const { return _Tc; }
		double Pc() const { return _Pc; }
		double MW() const { return _MW; }
	};
}

#endif // SPECIES_HPP_GUARD
