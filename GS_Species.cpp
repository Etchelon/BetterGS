#include "GS_Species.hpp"
#include "Utility.hpp"

using namespace std;

namespace BetterGS
{
	void NASA_Coefficients::print(ostream& os) const
	{
		os << "Lower bound = " << lowerBound << ", upper bound = " << upperBound << endl;

		os << "NASA coefficients:\n";
		for (size_t i = 1; i <= 9; ++i)
		{
			os << "a[" << i << "] = " << coefficients[i - 1] << endl;
		}
	}

	Species::Species(istream& is, const vector<Element>& elem)
		: formula(emptyString)
	{
		// Read all input data from the .gsi file
		read(is);

		// Parse the chemical formula, which at this point (after calling read) is a string at least one character long
		// Strip the phase specifier from the formula; e.g.: H2O(L) becomes H2O
		string f = formula;
		f.erase(find_if(f.begin(), f.end(), [](char c)
		{
			if (c == '(') return true;
			return false;
		}), f.end());

		static const string msg = "Error parsing the chemical formula, \"" + f + "\", of species \"" + name + "\": ";

		// Helper functor
		struct ElementInserter
		{
			map<Element, int>& elements;
			const vector<Element>& elem;

			ElementInserter(map<Element, int>& me, const vector<Element>& ve) : elements(me), elem(ve) { }

			void insert(const string& s, int n)
			{
				// Find the element from the list of elements read in the input file
				auto e = find_if(elem.cbegin(), elem.cend(), [s](const Element& el)
				{
					if (el.Name() == s)
						return true;

					return false;
				});

				if (e == elem.end())
					throw runtime_error(msg + "its formula contains an element, \"" + s + "\", that was not given in input!!\n");

				// Insert the element into the map
				if (!elements.insert(make_pair(*e, n)).second)
					throw runtime_error(msg + "its formula contains the same element, \"" + s + "\", multiple times!!\n");
			}
		} inserter(elements, elem);

		string s = emptyString;
		char c;
		istringstream iss(f);
		bool first = true; // To know if we've just parsed the first character of the formula; put to false right after it happens

		// Keep parsing the chemical formula, character by character
		while (iss >> c)
		{
			// If the character is a letter, check if it's upper case (new element) or lower case (second letter of an element)
			if (isalpha(c))
			{
				// Upper case
				if (c == toupper(c))
				{
					// If the parsing string is not empty, it contains the label of an element and I've just read another capital letter, therefore it's the first letter
					// of a new element; e.g.: formula == "CH4", s == "C", c == 'H' --> add C to the list of elements, with n = 1, reset s and add 'H' to it
					if (s != emptyString)
					{
						inserter.insert(s, 1);

						s = emptyString;
					}
					// When string s is empty, add the newly read character to it
					s += c;

					if (first)
						first = false;
				}
				// Lower case: s should contain an upper case letter, therefore the lower case character is part of an element label; e.g.: formula == "NaOH", s == "N", c == 'a'
				else
				{
					if (first)
						throw runtime_error(msg + "a chemical formula cannot begin with a lower case letter!!\n");
					if (s.length() == 0)
						throw runtime_error(msg + "its formula contains an atom, \"" + s + "\", with a label that begins with a lower case letter!!\n");

					s += c;
					if (s.length() > 2)
						throw runtime_error(msg + "its formula contains an atom, \"" + s + "\", with a label more than 3 characters long!!\n");
				}
			}
			// If the character is a digit, it is part of a number identifying the number of atoms of a given element in the current molecular species; e.g.: formula == "C3H22",
			// s == "H", c == '2' -> put c back into the stringstream and read 22 out of it
			else if (isdigit(c))
			{
				if (first)
					throw runtime_error(msg + "a chemical formula cannot begin with a number!!\n");

				iss.putback(c);
				int n;
				iss >> n;

				inserter.insert(s, n);

				s = emptyString;
			}
			else
			{
				throw runtime_error("Error reading species: a chemical formula must contain only alphanumeric characters!!\n");
			}
		}

		// After reading the last character, if the formula doesn't end with a number, there is still the label of some element buffered in s, therefore add it to the map with n == 1;
		// e.g.: formula == "NaOH", s == "H"
		if (s != emptyString)
			inserter.insert(s, 1);

		// Now compute the species's molecular weight from the atomic mass of its elements
		_MW = accumulate(elements.cbegin(), elements.cend(), 0., [](double a, const pair<Element, int>& p)
		{
			auto& e = p.first;
			int n = p.second;

			return a + e.AtomicMass()*n;
		});
	}

	void Species::read(istream& is)
	{
		static const string msg("Error in Species::read(): selected line is not properly formatted!!\n");
		string line;
		vector<string> words;

		// Read the first line
		// e.g.: C3H8      Propane
		getline_no_CR(is, line, '\n');
		words = split_line(line);

		if (words.size() < 2)
			throw runtime_error(msg + "The problematic line is the following:\n\n \"" + line + "\" \n\nThe line must contain at least two words: the species chemical formula and its label!!\n");

		formula = words[0];
		name    = emptyString;
		for (size_t i = 1; i < words.size(); ++i)
		{
			name.insert(name.end(), words[i].begin(), words[i].end());
			if (i != words.size() - 1)
				name += ' ';
		}

		// Read the second line
		// e.g.: 1, .0000000000D+00, -.1046800000D+09, .2703150000D+06, .3699500000D+03, .4255650000D+07, 0, 0, 2
		getline_no_CR(is, line, '\n');
		words = split_line(line, { ',' });

		if (words.size() != 9)
			throw runtime_error(msg + "The problematic line is the following:\n\n \"" + line + "\" \n\nThe line must contain exactly 9 numbers!!\n");

		phase      = parseNumber<int>(words[0]);
		density    = parseNumber<double>(words[1]);
		dH0f       = parseNumber<double>(words[2]);
		dS0f       = parseNumber<double>(words[3]);
		_Tc        = parseNumber<double>(words[4]);
		_Pc        = parseNumber<double>(words[5]);
		nIntervals = parseNumber<int>(words[8]);

		// Read temperature intervals
		// e.g.: .2000000000D+03,.1000000000D+04,.6000000000D+04,.0000000000D+00,.0000000000D+00,.0000000000D+00
		nasa.resize(nIntervals);

		getline_no_CR(is, line, '\n');
		words = split_line(line, { ',' });

		if (words.size() != 6)
			throw runtime_error(msg + "The problematic line is the following:\n\n \"" + line + "\" \n\nThe line must contain exactly 6 numbers!!\n");

		for (size_t i = 0; i < nIntervals; ++i)
		{
			nasa[i].lowerBound = parseNumber<double>(words[i]);
			nasa[i].upperBound = parseNumber<double>(words[i + 1]);
		}

		// Read NASA coefficients for every temperature interval
		for (size_t i = 0; i < nIntervals; ++i)
		{
			// Read two lines, one made of 5 coefficients, the other one made of 4 coefficients
			getline_no_CR(is, line, '\n');
			words = split_line(line, { ',' });

			if (words.size() != 5)
				throw runtime_error(msg + "The problematic line is the following:\n\n \"" + line + "\" \n\nThe line must contain exactly 5 numbers!!\n");

			getline_no_CR(is, line, '\n');
			vector<string> temp = split_line(line, { ',' });
			words.insert(words.end(), temp.cbegin(), temp.cend());

			if (words.size() != 9)
				throw runtime_error(msg + "The problematic line is the following:\n\n \"" + line + "\" \n\nThe line must contain exactly 4 numbers!!\n");

			for (size_t k = 0; k < 9; ++k)
				nasa[i].coefficients[k] = parseNumber<double>(words[k]);
		}
	}

	ostream& operator<<(ostream& os, const Species& species)
	{
		if (species.formula == emptyString)
		{
			os << "Empty Species!!\n";
			return os;
		}

		os << "Species " << species.name << ", with formula: " << species.formula << " and with critical temperature = " << species._Tc << " [K]" << endl;
		for_each(species.nasa.cbegin(), species.nasa.cend(), [&os](const NASA_Coefficients& val)
		{
			val.print(os);
		});

		return os;
	}
}
