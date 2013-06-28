#ifndef GS_UTILITY_HPP_GUARD
#define GS_UTILITY_HPP_GUARD

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

std::vector<std::string> split_line(const std::string& s, const std::vector<char>& delim = {' '});

template<class Container, class T>
inline
bool contains(const Container& c, const T& val)
{
	return std::find(c.cbegin(), c.cend(), val) != c.cend();
}

template<class T>
T parseNumber(std::string s)
{
	static_assert(std::is_arithmetic<T>::value, "Parse number cannot be instantiated to parse a string to a non-arithmetic type!!\n");

	// Replace FORTRAN 'D' with 'E' in double numbers
	size_t pos = s.find("D");
    if (pos != std::string::npos)
		s.replace(pos, 1, "E");

	std::istringstream iss(s);
	T ret;

    if (std::is_same<T, int>::value && pos != std::string::npos)
        throw std::runtime_error("Error in parseNumber() - The int isn't properly formatted!!\n");

	if (!(iss >> ret))
        throw std::runtime_error("Error in parseNumber() - The string doesn't contain a properly formatted number!!\n");

	return ret;
}

template<class T>
inline
void remove_carriage_return(std::basic_string<T>& s)
{
	static_assert(std::is_same<T, char>::value || std::is_same<T, wchar_t>::value, "Function remove_carriage_return can only accept string or wstring!!\n");

	if (*(s.rbegin()) == '\r')
		s.pop_back();
}

inline
void getline_no_CR(std::istream& is, std::string& line, char delim = '\n')
{
	std::getline(is, line, delim);
	remove_carriage_return(line);
}



#endif // GS_UTILITY_HPP_GUARD
