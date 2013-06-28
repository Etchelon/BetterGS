/* DIAMOCI DENTRO! :) AB
HOOORRAAAAY!!!!! MG */

#include "GS_Element.hpp"
#include "GS_Species.hpp"
#include "Utility.hpp"
#include <fstream>

using namespace std;
using namespace BetterGS;

vector<Element> elements;
static const string fileTestElement{"../BetterGS/Test Element.txt"};

int main(int arcg, char* argv[])
{
	{
		// Open input file stream
		bool binary = false;
		ifstream ifs;
		if (binary)
			ifs.open(fileTestElement, ios_base::binary);
		else
			ifs.open(fileTestElement);

		if (!ifs)
			throw runtime_error("Couldn't open the input file!!\n");

		// Find the beginning of the Element Data section
		string line;
		while (getline_no_CR(ifs, line, '\n'), line != "$* ELEMENT DATA")
		{	
			if (ifs.eof())
			{
				cout << "Cannot find Species Data!!" << endl;
				return 0;
			}
		}
	
		// Save the beginning of the Element Data section
		streampos begin = ifs.tellg();

		// Find the end beginning of the Element Data section and count the lines
		int nLines = 0;
		while (getline_no_CR(ifs, line, '\n'), line != "$* END OF ELEMENT DATA") { ++nLines; } // Do nothing

		// Create a vector of nLines elements
		ifs.seekg(begin);
		elements.resize(nLines);

		// Read element data
		for_each(elements.begin(), elements.end(), [&ifs](Element& elem)
		{
			elem.read(ifs);
		});
	
		// Print each element
		for_each(elements.begin(), elements.end(), [](const Element& elem)
		{
			cout << elem << endl;
		});
	}
	{
		// Open input file stream
		ifstream ifs(fileTestElement);
		if (!ifs)
			throw runtime_error("Couldn't open the input file!");

		// Find the beginning of the Element Data section
		string line;
		while (getline_no_CR(ifs, line, '\n'), line != "$* SPECIES DATA")
		{
			if (ifs.eof())
			{
				cout << "Cannot find Species Data!!" << endl;
				return 0;
			}
		}
	
		// Save the beginning of the Element Data section
		streampos begin = ifs.tellg();

		// Find the end beginning of the Element Data section and count the lines
		try
		{
			Species species(ifs, elements);
			cout << species;
			cout << "The molecular weight of this species is: " << species.MW() << " [g/mol]" << endl;
		}
		catch (const exception& e)
		{
			cout << e.what();
		}
	}

	return 0;
}
