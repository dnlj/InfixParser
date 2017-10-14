// InfixParser
#include <InfixParser/Evaluator.hpp>
#include <InfixParser/InfixParser.hpp>

namespace InfixParser {
	Evaluator::Evaluator() {
	}

	int Evaluator::evaluate(const std::string& equation) {
		// Ensure we have a non-empty equation
		if (equation.empty()) {
			throw EvaluationException{"Evaluator::evaluate only operates on non-empty equations."};
		}

		// Ensure our stacks are empty
		operands = decltype(operands){};
		operators = decltype(operators){};
		operator_depth = 1;

		// Get some useful iterators
		auto begin = equation.cbegin();
		auto current = begin;
		auto end = equation.cend();

		// Parse the string
		try {
			while (current != end) {
				// Ignore whitespaces
				if (is_whitespace(*current)) {
					++current;
					continue;
				}

				// Handle numbers and tokens
				if (is_number(*current)) {
					if (operator_depth > 0) {
						operands.push(read_number(current, end));
						operator_depth = 0;
					} else {
						throw EvaluationException{"Expected operator."};
					}

					expect_operand = false;
				} else {
					handle_token(current, end);
				}
			}

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
			throw_annotated(equation, except.what(), current - begin - 1);
		} catch (OperatorException& except) {
			throw_annotated(equation, except.what(), current - begin - 1);
		}

		// Get the result
		return operands.top();
	}

	const Operator* Evaluator::read_token(std::string::const_iterator& begin, const std::string::const_iterator& end) {
		if (begin == end) { return nullptr; }

		int next_offset = 1;
		const Operator* op = nullptr;

		// Translate from tokens to operators
		if (begin[0] == '+') {
			if (begin + 1 != end && begin[1] == '+') {
				op = &Operator::PRE_INCREMENT;
				next_offset = 2;
			} else {
				op = (&Operator::ADD);
			}
		} else if (begin[0] == '-') {
			if (begin + 1 != end && begin[1] == '-') {
				op = (&Operator::PRE_DECREMENT);
				next_offset = 2;
			} else {
				if (operator_depth == 0) {
					op = (&Operator::SUBTRACT);
				} else {
					op = (&Operator::NEGATE);
				}
			}
		} else if (begin[0] == '>') {
			if (begin + 1 != end && begin[1] == '=') {
				op = (&Operator::GREATER_OR_EQUAL);
				next_offset = 2;
			} else {
				op = (&Operator::GREATER);
			}
		} else if (begin[0] == '<') {
			if (begin + 1 != end && begin[1] == '=') {
				op = (&Operator::LESS_OR_EQUAL);
				next_offset = 2;
			} else {
				op = (&Operator::LESS);
			}
		} else if (begin[0] == '!') {
			if (begin + 1 != end && begin[1] == '=') {
				op = (&Operator::NOT_EQUAL);
				next_offset = 2;
			} else {
				op = (&Operator::NOT);
			}
		} else if (begin[0] == '&') {
			if (begin + 1 != end && begin[1] == '&') {
				op = (&Operator::AND);
				next_offset = 2;
			} else {
				++begin;
				throw EvaluationException{"Extraneous \"&\"."};
			}
		} else if (begin[0] == '|') {
			if (begin + 1 != end && begin[1] == '|') {
				op = (&Operator::OR);
				next_offset = 2;
			} else {
				++begin;
				throw EvaluationException{"Extraneous \"|\"."};
			}
		} else if (begin[0] == '=') {
			if (begin + 1 != end && begin[1] == '=') {
				op = (&Operator::EQUAL);
				next_offset = 2;
			} else {
				++begin;
				throw EvaluationException{"Extraneous \"=\"."};
			}
		} else if (begin[0] == '(') {
			op = (&Operator::LEFT_PAREN);
		} else if (begin[0] == ')') {
			op = (&Operator::RIGHT_PAREN);
		} else if (begin[0] == '^') {
			op = (&Operator::POWER);
		} else if (begin[0] == '*') {
			op = (&Operator::MULTIPLY);
		} else if (begin[0] == '/') {
			op = (&Operator::DIVIDE);
		} else if (begin[0] == '%') {
			op = (&Operator::REMAINDER);
		}

		begin += next_offset;
		return op;
	}

	void Evaluator::handle_token(std::string::const_iterator& begin, const std::string::const_iterator& end) {
		if (begin == end) { return; }

		// Ensure we are dealing with a token
		if (is_whitespace(*begin)) { return; }
		if (is_number(*begin)) { return; }

		// Translate from a token to an operator
		auto op = read_token(begin, end);

		if (op == nullptr) {
			throw EvaluationException{"Unknown operator."};
		}

		// Handle the operator
		handle_operator(op);

		// Handle the rest of the string
		handle_token(begin, end);
	}

	void Evaluator::handle_operator(const Operator* op) {
		// Get useful information about the operator
		const auto is_right_associative = op->is_right_associative();
		const auto precedence = op->precedence();

		// Increase operator depth
		++operator_depth;

		// Store if we are expecting an operand in the future.
		if (is_right_associative) {
			expect_operand = true;
		}

		// Handle left parentheses
		if (op == &Operator::LEFT_PAREN) {
			operators.push(op);
			return;
		}

		// Error if we were expecting an operand
		if (!is_right_associative && expect_operand) {
			throw EvaluationException{"Expected operand."};
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
			
			if (precedence <= top_prec && !is_right_associative) {
				operators.top()->apply(operands);
				operators.pop();
			} else {
				break;
			}
		}

		// Add the operator to the stack
		operators.push(op);
	}

	void Evaluator::throw_annotated(const std::string& equation, std::string error, size_t pos) {
		error += " @ character " + std::to_string(pos) + '\n';
		error += equation + '\n';
		error += std::string(pos, ' ') + "^\n";
		throw EvaluationException{error};
	}
}