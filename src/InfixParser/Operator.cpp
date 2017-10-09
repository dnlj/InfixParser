#include <InfixParser/Operator.hpp>

namespace InfixParser {
	Operator::Operator(std::string as_string, int precedence, bool right_associative, OperatorFunction function)
		: as_string{std::move(as_string)}
		, precedence_value{precedence}
		, right_associative{right_associative}
		, function{function} {
	};

	std::string Operator::to_string() const {
		return as_string;
	}

	int Operator::precedence() const {
		return precedence_value;
	}

	bool Operator::is_right_associative() const {
		return right_associative;
	}

	void Operator::apply(OperandStack& operands) const {
		function(operands);
	}
}

// Predefined operators
namespace InfixParser {
	const Operator Operator::NEGATE = {"N", 10, true, [](OperandStack& operands) {
		if (operands.empty()) { throw OperatorException{"Operator N (NEGATE) requires at least one operand."}; }

		auto& right = operands.top();
		right = -right;
	}};

	const Operator Operator::RIGHT_PAREN = {")", 9, false, [](OperandStack& operands) {
	}};

	const Operator Operator::NOT = {"!", 8, true, [](OperandStack& operands) {
		if (operands.empty()) { throw OperatorException{"Operator ! (NOT) requires at least one operand."}; }

		auto& right = operands.top();
		right = !right;
	}};

	const Operator Operator::PRE_INCREMENT = {"++", 8, true, [](OperandStack& operands) {
		if (operands.empty()) { throw OperatorException{"Operator ++ (PRE_INCREMENT) requires at least one operand."}; }

		auto& right = operands.top();
		right = ++right;
	}};

	const Operator Operator::PRE_DECREMENT = {"--", 8, true, [](OperandStack& operands) {
		if (operands.empty()) { throw OperatorException{"Operator -- (PRE_DECREMENT) requires at least one operand."}; }

		auto& right = operands.top();
		right = --right;
	}};

	const Operator Operator::POWER = {"^", 7, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator ^ (POWER) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		auto res = round(pow(static_cast<double>(left), static_cast<double>(right)));

		left = static_cast<decltype(right)>(res);
	}};

	const Operator Operator::MULTIPLY = {"*", 6, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator * (MULTIPLY) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();

		left = left * right;
	}};

	const Operator Operator::DIVIDE = {"/", 6, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator / (DIVIDE) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		if (right == 0) {
			throw OperatorException{"Division by zero."};
		}

		auto& left = operands.top();
		auto res = round(static_cast<double>(left) / static_cast<double>(right));

		left = static_cast<decltype(right)>(res);
	}};

	const Operator Operator::REMAINDER = {"%", 6, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator % (REMAINDER) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		if (right == 0) {
			throw OperatorException{"Remainder cannot be found when dividing by zero."};
		}
		
		auto& left = operands.top();
		left = left % right;
	}};

	const Operator Operator::ADD = {"+", 5, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator + (ADD) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left + right;
	}};

	const Operator Operator::SUBTRACT = {"-", 5, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator - (SUBTRACT) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left - right;
	}};

	const Operator Operator::GREATER = {">", 4, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator > (GREATER) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left > right;
	}};

	const Operator Operator::GREATER_OR_EQUAL = {">=", 4, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator >= (GREATER_OR_EQUAL) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left >= right;
	}};

	const Operator Operator::LESS = {"<", 4, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator < (LESS) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left < right;
	}};

	const Operator Operator::LESS_OR_EQUAL = {"<=", 4, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator <= (LESS_OR_EQUAL) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left <= right;
	}};

	const Operator Operator::EQUAL = {"==", 3, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator == (EQUAL) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left == right;
	}};

	const Operator Operator::NOT_EQUAL = {"!=", 3, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator != (NOT_EQUAL) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left != right;
	}};

	const Operator Operator::AND = {"&&", 2, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator && (AND) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left && right;
	}};

	const Operator Operator::OR = {"||", 1, false, [](OperandStack& operands) {
		if (operands.size() < 2) { throw OperatorException{"Operator || (OR) requires at least two operands."}; }

		auto right = operands.top();
		operands.pop();

		auto& left = operands.top();
		left = left || right;
	}};

	const Operator Operator::LEFT_PAREN = {"(", 0, false, [](OperandStack& operands) {
	}};
}