#pragma once

// STD
#include <string>
#include <utility>
#include <vector>
#include <stack>

// InfixParser
#include <InfixParser/Operator.hpp>

namespace InfixParser {
	class EvaluationException : public std::runtime_error {
		using runtime_error::runtime_error;
	};

	/**
	 * @brief Used to evaluate an infix string equation.
	 *
	 * Example usage:
	 * @code
	 * Evaluator evaluator;
	 * auto result = evaluator.evaluate("(1+2)*3");
	 * @endcode
	 */
	class Evaluator {
		public:
			/**
			 * @brief Constructs an evaluator.
			 */
			Evaluator();

			/**
			 * @brief Evaluates the equation @p equation and returns the result.
			 */
			int evaluate(const std::string& equation);

		private:
			/** Stores all active operands */
			OperandStack operands;

			/** Stores all active operators */
			std::stack<const Operator*> operators;

			/** The current operator depth */
			int operator_depth = 1;

			/** True if an operand is expected. Used only for error reporting. */
			bool expect_operand = true;

			/**
			 * @brief Reads the next valid token in the string [@p begin, @p end).
			 * After this function is called @p begin points to one past the end of the token.
			 *
			 * @param[in,out] begin The start of the string to read from.
			 * @param[in] end The end of the string to read from.
			 * @return The operator the read token represents. nullptr if no valid token could be read.
			 */
			const Operator* read_token(std::string::const_iterator& begin, const std::string::const_iterator& end);

			/**
			 * @brief Reads and processes the next token in the string defined by [@p begin, @p end).
			 * After this function is called @p begin points to one past the end of the token.
			 *
			 * @param[in,out] begin The beginning of the string to convert and evaluate.
			 * @param[in] end The beginning of the string to convert and evaluate.
			 * @throws EquationException When there is no token to read.
			 */
			void handle_token(std::string::const_iterator& begin, const std::string::const_iterator& end);

			/**
			 * @brief Handles the processing of @p op.
			 * @param[in] op The Operator to evaluate.
			 * @throws EquationException
			 */
			void handle_operator(const Operator* op);

			/**
			 * @brief Creates an annotated exception.
			 * @param[in] equation The original equation.
			 * @param[in] error The error message.
			 * @param[in] pos The position where the error occured.
			 * @throw EquationException
			 */
			void throw_annotated(const std::string& equation, std::string error, size_t pos);
	};
}