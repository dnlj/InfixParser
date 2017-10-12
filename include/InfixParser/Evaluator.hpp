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

			/**
			 * @brief Handles the processing of @p token.
			 * @param[in] token The token to convert and evaluate.
			 */
			void handle_token(const std::string& token);

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