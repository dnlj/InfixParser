#include <InfixParser/InfixParser.hpp>

bool InfixParser::is_number(char value) {
	return (value >= '0') && (value <= '9');
}

bool InfixParser::is_whitespace(char value) {
	return (value == ' ') || (value == '\t');
}

int InfixParser::read_number(std::string::const_iterator& begin, std::string::const_iterator end) {
	std::string num;
	
	// Read until the first non-number character
	while (begin != end) {
		if (!is_number(*begin)) { break; }

		num += *begin;
		++begin;
	}

	// Convert the number string to an integer
	return std::stoi(num);
}
