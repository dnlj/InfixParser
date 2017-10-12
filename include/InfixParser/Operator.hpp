#pragma once

// STD
#include <string>
#include <stack>

// InfixParser
#include <InfixParser/InfixParser.hpp>

namespace InfixParser {
	class OperatorException : public std::runtime_error {
		using runtime_error::runtime_error;
	};

	/**
	 * @brief Represents an operator.
	 *
	 * Example usage: 
	 * @code
	 * const Operator Operator::ADD = {"+", 5, false, [](OperandStack& operands) {
	 *		if (operands.size() < 2) { throw OperatorException{"Operator + (ADD) requires at least two operands."}; }
	 *	
	 *		auto right = operands.top();
	 *		operands.pop();
	 *	
	 *		auto& left = operands.top();
	 *		left = left + right;
	 * }};
	 * @endcode
	 */
	class Operator {
		public:
			/** The type of the funciton called when an Operator is applied. */
			using OperatorFunction = void(*)(OperandStack&);

			/**
			 * @brief Create an Operator with a given string representation, precedence, associativity, and function.
			 * @param[in] as_string The string representation of the Operator.
			 * @param[in] precedence The precedence of the Operator.
			 * @param[in] right_associative Sets the Operator to be right associative.
			 * @param[in] function The function to call when this operator is applied.
			 */
			Operator(std::string as_string, int precedence, bool right_associative, OperatorFunction function);

			/**
			 * @brief Get the string representation of this Operator.
			 * @return The string representation of this Operator.
			 */
			std::string to_string() const;

			/**
			 * @brief Get the precedence of this Operator.
			 * @return The precedence of this Operator.
			 */
			int precedence() const;

			/**
			 * @brief Checks if this Operator is right associative.
			 * @return True if this Operator is right associative, otherwise false.
			 */
			bool is_right_associative() const;

			/**
			 * @brief Applies this Operator to the operand stack @p operands.
			 * @param[in,out] operands The operands to apply this Operator to.
			 */
			void apply(OperandStack& operands) const;

		private:
			/** The string representation of this operator */ 
			const std::string as_string;

			/** The precedence of this operator */
			const int precedence_value;

			/** The associativity of this operator */
			const bool right_associative;

			/** The function that is called when this operator is applied */
			const OperatorFunction function;
		
		// Predefined operators
		public:
			static const Operator NEGATE;
			static const Operator RIGHT_PAREN;
			static const Operator NOT;
			static const Operator PRE_INCREMENT;
			static const Operator PRE_DECREMENT;
			static const Operator POWER;
			static const Operator MULTIPLY;
			static const Operator DIVIDE;
			static const Operator REMAINDER;
			static const Operator ADD;
			static const Operator SUBTRACT;
			static const Operator GREATER;
			static const Operator GREATER_OR_EQUAL;
			static const Operator LESS;
			static const Operator LESS_OR_EQUAL;
			static const Operator EQUAL;
			static const Operator NOT_EQUAL;
			static const Operator AND;
			static const Operator OR;
			static const Operator LEFT_PAREN;
	};
}