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
			 * @brief Handles the processing of the token defined by [@p begin, @p end).
			 * @param[in] begin The beginning of the token to convert and evaluate.
			 * @param[in] end The beginning of the token to convert and evaluate.
			 */
			void handle_token(std::string::iterator begin, const std::string::iterator& end);

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