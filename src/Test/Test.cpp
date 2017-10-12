// STD
#include <iostream>

// Test
#include <Test/Test.hpp>

// InfixParser
#include <InfixParser/Evaluator.hpp>

void Test::check_equation(const std::string& equation, int expected) {
	static InfixParser::Evaluator evaluator;
	auto value = evaluator.evaluate(equation);

	// Print a warning if equation does not evaluate to expected
	if (value != expected) {
		std::cout << "Incorrect equation: " << equation << " is " << value << " which does not equal " << expected << std::endl;
	}
}

