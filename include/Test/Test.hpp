#pragma once

// STD
#include <string>

namespace Test {
	/**
	 * @brief Checks if @p equation evaluates to @p expected using InfixParser::Evaluator::evaluate.
	 * @param[in] equation The equation to check.
	 * @param[in] expected The expected value.
	 */
	void check_equation(const std::string& equation, int expected);

	/**
	 * @brief Checks if @p equation throws an exception when evaluated using InfixParser::Evaluator::evaluate.
	 * @param[in] equation The equation to check.
	 * @param[in] print If set to true then when an exception is thrown exception.what() will be printed.
	 */
	void check_equation_throws(const std::string& equation, bool print);
}