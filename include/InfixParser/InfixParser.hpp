#pragma once

// STD
#include <string>
#include <stack>

namespace InfixParser {
	/** The operand stack type. */
	using OperandStack = std::stack<int>;

	/**
	 * @brief Checks if @p value is a number.
	 * @param[in] value The value to check.
	 * @return True if @p value is a number, false otherwise.
	 */
	bool is_number(char value);

	/**
	 * @brief Checks if @p value is a whitespace character.
	 * @param[in] value The value to check.
	 * @return True if @p value is a whitespace character, false otherwise.
	 */
	bool is_whitespace(char value);

	/**
	 * @brief Reads the first number from the string defined by @p begin, and @p end.
	 * After this function is called @p begin points to one past the end of the number.
	 *
	 * @param[in,out] begin The beginning of the string.
	 * @param[in] end The end of the string.
	 */
	int read_number(std::string::const_iterator& begin, std::string::const_iterator end);

	/**
	 * @brief Reads the first token from the string defined by @p begin, and @p end.
	 * After this function is called @p begin points to one past the end of the token.
	 *
	 * @param[in,out] begin The beginning of the string.
	 * @param[in] end The end of the string.
	 */
	std::string read_token(std::string::const_iterator& begin, std::string::const_iterator end);
}