// STD
#include <iostream>
#include <stack>

// InfixParser
#include <InfixParser/InfixParser.hpp>
#include <InfixParser/Evaluator.hpp>

// Test
#include <Test/Test.hpp>


void equation_tests() {
	// Negation
	Test::check_equation("2", 2);
	Test::check_equation("1", 1);
	Test::check_equation("0", 0);
	Test::check_equation("-0", -0);
	Test::check_equation("-1", -1);
	Test::check_equation("-2", -2);

	// Not
	Test::check_equation("!2", 0);
	Test::check_equation("!1", 0);
	Test::check_equation("!0", 1);
	Test::check_equation("!-0", 1);
	Test::check_equation("!-1", 0);
	Test::check_equation("!-2", 0);

	Test::check_equation("!!2", 1);
	Test::check_equation("!!1", 1);
	Test::check_equation("!!0", 0);
	Test::check_equation("!!-0", 0);
	Test::check_equation("!!-1", 1);
	Test::check_equation("!!-2", 1);
	
	Test::check_equation("!!!2", 0);
	Test::check_equation("!!!1", 0);
	Test::check_equation("!!!0", 1);
	Test::check_equation("!!!-0", 1);
	Test::check_equation("!!!-1", 0);
	Test::check_equation("!!!-2", 0);
	
	// Pre Increment
	Test::check_equation("++2", 3);
	Test::check_equation("++1", 2);
	Test::check_equation("++0", 1);
	Test::check_equation("++-0", 1);
	Test::check_equation("++-1", 0);
	Test::check_equation("++-2", -1);
	
	// Pre Decrement
	Test::check_equation("--2", 1);
	Test::check_equation("--1", 0);
	Test::check_equation("--0", -1);
	Test::check_equation("---0", -1);
	Test::check_equation("---1", -2);
	Test::check_equation("---2", -3);
	
	// Power
	Test::check_equation("2^2", 4);
	Test::check_equation("2^1", 2);
	Test::check_equation("2^0", 1);
	Test::check_equation("2^-1", 1);
	Test::check_equation("2^-2", 0);
	
	Test::check_equation("0^2", 0);
	Test::check_equation("0^1", 0);
	Test::check_equation("0^0", 1);
	
	Test::check_equation("-2^2", 4);
	Test::check_equation("-2^1", -2);
	Test::check_equation("-2^0", 1);
	Test::check_equation("-2^-1", -1);
	Test::check_equation("-2^-2", 0);
	
	// Multiplication
	Test::check_equation("2 * 3", 6);
	Test::check_equation("2 * -3", -6);
	Test::check_equation("-2 * 3", -6);
	Test::check_equation("-2 * -3", 6);
	Test::check_equation("2 * 0", 0);
	Test::check_equation("2 * 1", 2);
	
	// Division
	Test::check_equation("1 / 3", 0);
	Test::check_equation("4 / 2", 2);
	Test::check_equation("-4 / 2", -2);
	Test::check_equation("-4 / -2", 2);
	Test::check_equation("4 / -2", -2);
	Test::check_equation("0 / 2", 0);
	Test::check_equation("4 / 1", 4);
	
	// Remainder
	Test::check_equation("5 % 3", 2);
	Test::check_equation("4 % 3", 1);
	Test::check_equation("3 % 3", 0);
	Test::check_equation("2 % 3", 2);
	Test::check_equation("1 % 3", 1);
	Test::check_equation("0 % 3", 0);
	Test::check_equation("-0 % 3", -0);
	Test::check_equation("-1 % 3", -1);
	Test::check_equation("-2 % 3", -2);
	Test::check_equation("-3 % 3", -0);
	Test::check_equation("-4 % 3", -1);
	Test::check_equation("-5 % 3", -2);
	
	Test::check_equation("5 % -3", 2);
	Test::check_equation("4 % -3", 1);
	Test::check_equation("3 % -3", 0);
	Test::check_equation("2 % -3", 2);
	Test::check_equation("1 % -3", 1);
	Test::check_equation("0 % -3", 0);
	Test::check_equation("-0 % -3", -0);
	Test::check_equation("-1 % -3", -1);
	Test::check_equation("-2 % -3", -2);
	Test::check_equation("-3 % -3", -0);
	Test::check_equation("-4 % -3", -1);
	Test::check_equation("-5 % -3", -2);
	
	// Addition
	Test::check_equation("2 + 3", 5);
	Test::check_equation("2 + 0", 2);
	Test::check_equation("0 + 0", 0);
	Test::check_equation("1 + -2", -1);
	Test::check_equation("3 + -2", 1);
	Test::check_equation("1 + -0", 1);
	Test::check_equation("-3 + 1", -2);
	Test::check_equation("-3 + -1", -4);
	
	// Subtraction
	Test::check_equation("2 - 3", -1);
	Test::check_equation("3 - 2", 1);
	Test::check_equation("2 - 0", 2);
	Test::check_equation("0 - 2", -2);
	Test::check_equation("-3 - 1", -4);
	Test::check_equation("-3 - 0", -3);
	
	// Greater than
	Test::check_equation("2 > 2", false);
	Test::check_equation("2 > 0", true);
	Test::check_equation("2 > -2", true);
	
	Test::check_equation("0 > 2", false);
	Test::check_equation("0 > 0", false);
	Test::check_equation("0 > -2", true);
	
	Test::check_equation("-2 > 2", false);
	Test::check_equation("-2 > 0", false);
	Test::check_equation("-2 > -2", false);
	
	// Greater than or equal
	Test::check_equation("2 >= 2", true);
	Test::check_equation("2 >= 0", true);
	Test::check_equation("2 >= -2", true);
	
	Test::check_equation("0 >= 2", false);
	Test::check_equation("0 >= 0", true);
	Test::check_equation("0 >= -2", true);
	
	Test::check_equation("-2 >= 2", false);
	Test::check_equation("-2 >= 0", false);
	Test::check_equation("-2 >= -2", true);
	
	// Less than
	Test::check_equation("2 < 2", false);
	Test::check_equation("2 < 0", false);
	Test::check_equation("2 < -2", false);
	
	Test::check_equation("0 < 2", true);
	Test::check_equation("0 < 0", false);
	Test::check_equation("0 < -2", false);
	
	Test::check_equation("-2 < 2", true);
	Test::check_equation("-2 < 0", true);
	Test::check_equation("-2 < -2", false);
	
	// Less than or equal
	Test::check_equation("2 <= 2", true);
	Test::check_equation("2 <= 0", false);
	Test::check_equation("2 <= -2", false);
	
	Test::check_equation("0 <= 2", true);
	Test::check_equation("0 <= 0", true);
	Test::check_equation("0 <= -2", false);
	
	Test::check_equation("-2 <= 2", true);
	Test::check_equation("-2 <= 0", true);
	Test::check_equation("-2 <= -2", true);
	
	// Equal
	Test::check_equation("2 == 2", true);
	Test::check_equation("2 == 0", false);
	Test::check_equation("2 == -2", false);
	
	Test::check_equation("0 == 2", false);
	Test::check_equation("0 == 0", true);
	Test::check_equation("0 == -2", false);
	
	Test::check_equation("-2 == 2", false);
	Test::check_equation("-2 == 0", false);
	Test::check_equation("-2 == -2", true);
	
	// Not Equal
	Test::check_equation("2 != 2", false);
	Test::check_equation("2 != 0", true);
	Test::check_equation("2 != -2", true);
	
	Test::check_equation("0 != 2", true);
	Test::check_equation("0 != 0", false);
	Test::check_equation("0 != -2", true);
	
	Test::check_equation("-2 != 2", true);
	Test::check_equation("-2 != 0", true);
	Test::check_equation("-2 != -2", false);
	
	// And
	Test::check_equation("1 && 1", true);
	Test::check_equation("1 && 0", false);
	Test::check_equation("0 && 1", false);
	
	Test::check_equation("0 && 0", false);
	
	Test::check_equation("-1 && -1", true);
	Test::check_equation("-1 && 0", false);
	Test::check_equation("0 && -1", false);
	
	// Or
	Test::check_equation("1 || 1", true);
	Test::check_equation("1 || 0", true);
	Test::check_equation("0 || 1", true);
	
	Test::check_equation("0 || 0", false);
	
	Test::check_equation("-1 || -1", true);
	Test::check_equation("-1 || 0", true);
	Test::check_equation("0 || -1", true);
}

void equation_tests_mixed() {
	// From project_1.pdf
	Test::check_equation("1+2*3", 7);
	Test::check_equation("2+2^2*3", 14);
	Test::check_equation("1==2", 0);
	Test::check_equation("1+3 > 2", 1);
	Test::check_equation("(4>=4) && 0", 0);
	Test::check_equation("(1+2)*3", 9);
	Test::check_equation("++++2-5*(3^2)", -41);

	// Others
	Test::check_equation("-2 + (3%5)^3*-1 + ++3", -25);
	Test::check_equation("6/3 + (4==--5)", 3);
	Test::check_equation("1 == 0 || 1 != 0", true);
	Test::check_equation("(3==-2&&1!=0) || -39==-39", true);
}

void equation_throws_tests(bool print) {
	// From project_1.pdf
	Test::check_equation_throws(")3+2", print);
	Test::check_equation_throws("<3+2", print);
	Test::check_equation_throws("3&&&&5", print);
	Test::check_equation_throws("15+3 2", print);
	Test::check_equation_throws("10+ ++<3", print);
	Test::check_equation_throws("1/0", print);

	// Other
	Test::check_equation_throws("(<3+2)", print);
	Test::check_equation_throws("(!<3+2)", print);
	Test::check_equation_throws("(3+2) * (/3)", print);
	Test::check_equation_throws("(3-2)++", print);
	Test::check_equation_throws("(3-2)++1", print);
	Test::check_equation_throws("(3-2)!", print);
	Test::check_equation_throws("3-!", print);
	Test::check_equation_throws("3/(2!)", print);
	Test::check_equation_throws("2 + x", print);
	Test::check_equation_throws("2 ? 3", print);
	Test::check_equation_throws("3 - + 2", print);
	Test::check_equation_throws("3 % 0", print);
	Test::check_equation_throws("3 | 2", print);
	Test::check_equation_throws("3 & 2", print);
	Test::check_equation_throws("3 = 2", print);
	Test::check_equation_throws("", print);
}

void run_tests() {
	equation_tests();
	equation_tests_mixed();
	equation_throws_tests(true);
}

int main() {
	run_tests();
	std::cout << "Done." << std::endl;
	getchar();
	return 0;
}