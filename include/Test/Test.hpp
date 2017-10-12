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
}