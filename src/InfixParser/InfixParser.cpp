#include <InfixParser/InfixParser.hpp>

bool InfixParser::is_number(char value) {
	return (value >= '0') && (value <= '9');
}

bool InfixParser::is_whitespace(char value) {
	return (value == ' ') || (value == '\t');
}

int InfixParser::read_number(std::string::const_iterator& begin, std::string::const_iterator end) {
	std::string num;
	
	while (begin != end) {
		if (!is_number(*begin)) { break; }

		num += *begin;
		++begin;
	}

	return std::stoi(num);
}

std::string InfixParser::read_token(std::string::const_iterator& begin, std::string::const_iterator end) {
	std::string token;

	while (begin != end)  {
		if (is_whitespace(*begin)) { break; }
		if (is_number(*begin)) { break; }

		token += *begin;
		++begin;
	}

	return token;
}