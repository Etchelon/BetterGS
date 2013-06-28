#include "GS_Element.hpp"
#include "Utility.hpp"

using namespace std;

namespace BetterGS
{
	void Element::read(istream& is)
	{
		static const string msg("Error in Species::read(): selected line is not properly formatted!!\n");
		string line;

		// Read the line containing Element data
		// e.g.: C  .1201070000D+02 CO2          CO2          .3700000000D-03
		getline(is, line, '\n');
		vector<string> words = split_line(line);

		if (words.size() != 5)
			throw runtime_error(msg + "The problematic line is the following:\n\n \"" + line + "\" \n\nThe line must contain exactly 5 words!!\n");

		name = words[0];
		atomicMass = parseNumber<double>(words[1]);
		combustedStateSpecies = words[2];
		deadStateSpecies = words[3];
		ambientConc = parseNumber<double>(words[4]);
	}

	ostream& operator<<(ostream& os, const Element& elem)
	{
		if (elem.name == emptyString)
		{
			os << "Empty Element!!\n";
			return os;
		}

		os << "Element " << elem.name << ", with atomic mass = " << elem.atomicMass << " [g/mol]" << endl;
		os << "Has combusted state species: " << elem.combustedStateSpecies << ", dead state species: " << elem.deadStateSpecies << " and ambient conc = " << elem.ambientConc*100 << "%" << endl;
		return os;
	}
}
