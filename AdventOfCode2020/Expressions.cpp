#include "Expressions.h"
//#include <iostream>

namespace expr {

	EvalState::EvalState() {

	}
	EvalState::~EvalState() {

	}
	void EvalState::setValue(std::string var, int value) {
		symbolTable.insert({ var,value });
	}
	int EvalState::getValue(std::string var) {
		return symbolTable[var];
	}
	bool EvalState::isDefined(std::string var) {
		return symbolTable.find(var) != symbolTable.end();
	}

	Expression::Expression()
	{
	}
	Expression::~Expression()
	{
	}

	ConstantExp::ConstantExp(int value)
		:
		value(value)
	{
	}
	int ConstantExp::eval(EvalState& state)
	{
		return value;
	}
	std::string ConstantExp::toString()
	{
		return std::to_string(value);
	}
	ExpressionType ConstantExp::getType()
	{
		return ExpressionType::CONSTANT;
	}
	int ConstantExp::getValue()
	{
		return value;
	}

	CompoundExp::CompoundExp(std::string op, Expression* lhs, Expression* rhs)
		:
		op(op),
		lhs(lhs),
		rhs(rhs)
	{}
	CompoundExp::~CompoundExp()
	{
		delete lhs;
		delete rhs;
	}
	int CompoundExp::eval(EvalState& state)
	{
		
		int left = lhs->eval(state);
		int right = rhs->eval(state);
		if (op == "+") return left + right;
		if (op == "-") return left - right;
		if (op == "*") return left * right;
		if (op == "/") return left / right;
		std::cout << "Error, illegal operator in expression";
		return -1;
	}
	std::string CompoundExp::toString()
	{
		return "(" + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
	}
	ExpressionType CompoundExp::getType()
	{
		return ExpressionType::COMPOUND;
	}
	std::string CompoundExp::getOp()
	{
		return op;
	}
	Expression* CompoundExp::getLHS()
	{
		return lhs;
	}
	Expression* CompoundExp::getRHS()
	{
		return rhs;
	}
	void CompoundExp::setLHS(Expression* e)
	{
		lhs = e;
	}
	void CompoundExp::setRHS(Expression* e)
	{
		rhs = e;
	}


	bool isOperator(std::string token) {
		return	token == "+" || token == "-" || token == "*";
	}
	Expression* readTerm(std::queue<std::string>& tQueue);
	Expression* readExpression(std::queue<std::string>& tQueue) {
		Expression* exp = readTerm(tQueue);
		if (!tQueue.empty()) {
			std::string token = tQueue.front();
			if (getTokenType(token) != TokenType::NUMBER) {
				tQueue.pop();
				Expression* lhs = readExpression(tQueue);
				exp = new CompoundExp(token, lhs , exp);
			}
		}
		return exp;
	}
	Expression* readTerm(std::queue<std::string>& tQueue) {
		std::string token = tQueue.front(); tQueue.pop();
		if (getTokenType(token) == TokenType::NUMBER) return new ConstantExp(std::stoi(token));
		Expression* exp = readExpression(tQueue);
		return exp;
	}
	Expression* parseExp(std::queue<std::string>& tQueue)
	{
		Expression* exp = readExpression(tQueue);
		return exp;
	}
	TokenType getTokenType(std::string token) {
		char ch = token[0];
		if (isdigit(ch)) return TokenType::NUMBER;
		//if (isalnum(ch)) return TokenType::WORD;
		return TokenType::OPERATOR;
	}
}