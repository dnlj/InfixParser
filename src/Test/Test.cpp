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


void Test::check_equation_throws(const std::string& equation, bool print) {
	static InfixParser::Evaluator evaluator;
	bool thrown = false;

	// Check if an exception is thrown
	try {
		evaluator.evaluate(equation);
	} catch (InfixParser::EvaluationException& except) {
		thrown = true;

		if (print) {
			std::cout << except.what() << std::endl;
		}
	}

	// Print a warning if no exception is thrown
	if (!thrown) {
		std::cout << "No exception thrown for equation: " << equation << std::endl;
	}
}