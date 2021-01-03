#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <queue>

/* File: Expressions.h
 * -------------------
 * Defines a class hierarchy for processing arithmetic expressions
 *
 */

namespace expr {
	enum class ExpressionType{ CONSTANT, COMPOUND };
	enum class TokenType{ NUMBER, OPERATOR };
	TokenType getTokenType(std::string token);

	class EvalState {
	public:
		EvalState();
		~EvalState();
		void setValue(std::string var, int value);
		int getValue(std::string var);
		bool isDefined(std::string var);
	private:
		std::map<std::string, int> symbolTable;
	};

	// Base class
	class Expression {
	public:
		Expression();
		virtual ~Expression();
		virtual int eval(EvalState& state) = 0;
		virtual std::string toString() = 0;
		virtual ExpressionType getType() = 0;
	};

	// Derived Classes
	class ConstantExp : public Expression {
	public:
		ConstantExp(int value);
		virtual int eval(EvalState& state);
		virtual std::string toString();
		virtual ExpressionType getType();
		int getValue();
	private:
		int value;
	};

	class CompoundExp : public Expression {
	public:
		CompoundExp(std::string op, Expression* lhs, Expression* rhs);
		virtual ~CompoundExp();
		virtual int eval(EvalState& state);
		virtual std::string toString();
		virtual ExpressionType getType();
		std::string getOp();
		Expression* getLHS();
		Expression* getRHS();
		void setLHS(Expression* e);
		void setRHS(Expression* e);
	private:
		std::string op;
		Expression* lhs, * rhs;
	};

	Expression* parseExp(std::queue<std::string>& tQueue);
}

