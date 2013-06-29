#include "GS_Stream.hpp"
#include "Utility.hpp"

using namespace std;
using namespace BbMath;

namespace BetterGS
{
	void GS_Stream::read(istream& is)
	{
		static const string msg("Error in GS_Stream::read(): selected line is not properly formatted!!\n");
		string line;
		vector<string> words;

		// Read the first line
		// Amb .2881500000D+03 .1013250000D+06 .1000000000D+01 .6000000000D+00
		getline_no_CR(is, line, '\n');
		words = split_line(line);

		if (words[0] == "Amb")
		{
			if (words.size() != 5)
				throw runtime_error(msg + "The problematic line is the following:\n\n \"" + line + "\" \n\nThe line must contain exactly 5 words!!\n");

			id = 0;
			setT(parse_number<double>(words[1]));
			setP(parse_number<double>(words[2]));
			setMassFlow(parse_number<double>(words[3]));
			setHumidity(parse_number<double>(words[4]));
		}
	}
}
