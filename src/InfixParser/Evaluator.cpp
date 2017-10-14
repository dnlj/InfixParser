// InfixParser
#include <InfixParser/Evaluator.hpp>
#include <InfixParser/InfixParser.hpp>

namespace InfixParser {
	Evaluator::Evaluator() {
	}

	int Evaluator::evaluate(const std::string& equation) {
		// Ensure our stacks are empty
		operands = decltype(operands){};
		operators = decltype(operators){};
		operator_depth = 1;

		// Get some useful iterators
		auto begin = equation.cbegin();
		auto current = begin;
		auto end = equation.cend();

		// Used only for error reporting
		auto before = current;

		// Parse the string
		try {
			while (current != end) {
				// Ignore whitespaces
				if (is_whitespace(*current)) {
					++current;
					continue;
				}

				// Store location before reading for error reporting
				before = current;
				
				// Handle numbers and tokens
				if (is_number(*current)) {
					if (operator_depth > 0) {
						operands.push(read_number(current, end));
						operator_depth = 0;
					} else {
						throw EvaluationException{"Expected operand."};
					}

					expect_operand = false;
				} else {
					auto token = read_token(current, end);
					handle_token(token.begin(), token.end());
				}
			}

			// Update the current position for error reporting
			before = current - 1;

			// Apply any remaining operators
			while (!operators.empty()) {
				operators.top()->apply(operands);
				operators.pop();
			}

			if (expect_operand) {
				throw EvaluationException{"Expected operand after."};
			}

			// Ensure that all operands have been used
			if (operands.size() != 1) {
				throw EvaluationException{"Ill formed equation. To many operands."};
			}
		} catch (EvaluationException& except) {
			throw_annotated(equation, except.what(), before - begin);
		} catch (OperatorException& except) {
			throw_annotated(equation, except.what(), before - begin);
		}

		// Get the result
		return operands.top();
	}

	void Evaluator::handle_token(std::string::iterator begin, const std::string::iterator& end) {
		if (begin == end) { return; }
		int next_offset = 1;

		// Translate from tokens to operators
		if (begin[0] == '+') {
			if (begin + 1 != end && begin[1] == '+') {
				handle_operator(&Operator::PRE_INCREMENT);
				next_offset = 2;
			} else {
				handle_operator(&Operator::ADD);
			}
		} else if (begin[0] == '-') {
			if (begin + 1 != end && begin[1] == '-') {
				handle_operator(&Operator::PRE_DECREMENT);
				next_offset = 2;
			} else {
				if (operator_depth == 0) {
					handle_operator(&Operator::SUBTRACT);
				} else if (begin + 1 == end) {
					handle_operator(&Operator::NEGATE);
				} else {
					throw EvaluationException{"Extraneous \""+ std::string{begin, end} +"\"."};
				}
			}
		} else if (begin[0] == '>') {
			if (begin + 1 != end && begin[1] == '=') {
				handle_operator(&Operator::GREATER_OR_EQUAL);
				next_offset = 2;
			} else {
				handle_operator(&Operator::GREATER);
			}
		} else if (begin[0] == '<') {
			if (begin + 1 != end && begin[1] == '=') {
				handle_operator(&Operator::LESS_OR_EQUAL);
				next_offset = 2;
			} else {
				handle_operator(&Operator::LESS);
			}
		} else if (begin[0] == '!') {
			if (begin + 1 != end && begin[1] == '=') {
				handle_operator(&Operator::NOT_EQUAL);
				next_offset = 2;
			} else {
				handle_operator(&Operator::NOT);
			}
		} else if (begin[0] == '&') {
			if (begin + 1 != end && begin[1] == '&') {
				handle_operator(&Operator::AND);
				next_offset = 2;
			} else {
				throw EvaluationException{"Extraneous \"" + std::string{begin, end} + "\"."};
			}
		} else if (begin[0] == '|') {
			if (begin + 1 != end && begin[1] == '|') {
				handle_operator(&Operator::OR);
				next_offset = 2;
			} else {
				throw EvaluationException{"Extraneous \"" + std::string{begin, end} + "\"."};
			}
		} else if (begin[0] == '=') {
			if (begin + 1 != end && begin[1] == '=') {
				handle_operator(&Operator::EQUAL);
				next_offset = 2;
			} else {
				throw EvaluationException{"Extraneous \"" + std::string{begin, end} + "\"."};
			}
		} else if (begin[0] == '(') {
			handle_operator(&Operator::LEFT_PAREN);
		} else if (begin[0] == ')') {
			handle_operator(&Operator::RIGHT_PAREN);
		} else if (begin[0] == '^') {
			handle_operator(&Operator::POWER);
		} else if (begin[0] == '*') {
			handle_operator(&Operator::MULTIPLY);
		} else if (begin[0] == '/') {
			handle_operator(&Operator::DIVIDE);
		} else if (begin[0] == '%') {
			handle_operator(&Operator::REMAINDER);
		} else {
			throw EvaluationException{"Unknown operator \""+ std::string{begin, end} + "\"."};
		}

		// Handle the rest of the token
		handle_token(begin + next_offset, end);
	}

	void Evaluator::handle_operator(const Operator* op) {
		// Handle left parentheses
		if (op == &Operator::LEFT_PAREN) {
			operators.push(op);
			return;
		}

		// Handle right parentheses
		if (op == &Operator::RIGHT_PAREN) {
			// Apply all operators until a left parenthesis is found
			while (true) {
				if (operators.empty()) {
					throw EvaluationException{"Extraneous \"" + op->to_string() + "\"."};
				}

				if (operators.top() == &Operator::LEFT_PAREN) {
					break;
				}

				operators.top()->apply(operands);
				operators.pop();
			}

			// Remove the left parenthesis
			operators.pop();
		}

		// Handle all other operators
		while (!operators.empty()) {
			auto top_prec = operators.top()->precedence();
			auto op_prec = op->precedence();
			auto op_right_assoc = op->is_right_associative();
			
			if (op_prec <= top_prec && !op_right_assoc) {
				operators.top()->apply(operands);
				operators.pop();
			} else {
				break;
			}
		}

		// Store if we are expecting an operand in the future.
		if (op->is_right_associative()) {
			expect_operand = true;
		} else if (operands.empty()) {
			throw EvaluationException{"Expected operand."};
		}

		// Add the operator to the stack
		operators.push(op);
		++operator_depth;
	}

	void Evaluator::throw_annotated(const std::string& equation, std::string error, size_t pos) {
		error += " @ character " + std::to_string(pos) + '\n';
		error += equation + '\n';
		error += std::string(pos, ' ') + "^\n";
		throw EvaluationException{error};
	}
}