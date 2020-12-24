#pragma once
#include "Utils.h"

struct Instruction {
	std::string instr="";
	int val=-1;
	bool visited = false;
};


class Assembler {
public:
	enum class Validation {
		inf_loop,error,ok
	};
	Assembler(std::string filename = "Day8_input.txt") {
		std::ifstream in(filename);
		std::string str;
		int counter = 0;
		while (std::getline(in, str)) {
			std::vector<std::string> tokens = Utils::split(str, ' ');
			instructions.push_back({ tokens[0],std::stoi(tokens[1]) });
			if (tokens[0] == "nop" || tokens[0] == "jmp") {
				stack.push({ instructions.back(), counter });
			}
			counter++;
		}
	}
	std::pair<int,Validation> run() {
		for (auto& instr : instructions) {
			instr.visited = false;
		}
		int index = 0;
		int accumulator = 0;
		while (true) {
			if (index == instructions.size()) return { accumulator,Validation::ok };
			if (instructions[index].visited) return {accumulator, Validation::inf_loop};
			instructions[index].visited = true;
			std::string instr = instructions[index].instr;
			if (instr == "nop") {
				index += 1;
			}
			else if (instr == "acc") {
				accumulator += instructions[index].val;
				index += 1;
			}
			else if (instr == "jmp") {
				index += instructions[index].val;
			}
			else {
				std::cout << "ERROR";
				return { -1,Validation::error };
			}
		}
	}
	int fix() {
		auto res = run();
		Instruction correction;
		int pos = 0;
		while (res.second == Validation::inf_loop && !stack.empty())
		{
			correction = stack.top().first, pos = stack.top().second; stack.pop();
			nop_jmp_switch(pos);
			res = run();
			nop_jmp_switch(pos);
			std::cout << '.';
		}
		return res.first;
	}
private:
	void nop_jmp_switch(int pos) {
		if (instructions[pos].instr == "nop") instructions[pos].instr = "jmp";
		else if (instructions[pos].instr == "jmp") instructions[pos].instr = "nop";
	}
	std::vector<Instruction> instructions;
	std::stack<std::pair<Instruction, int>> stack;
};