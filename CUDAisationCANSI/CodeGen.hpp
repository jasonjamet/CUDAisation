#ifndef CODE_GEN_HPP
#define CODE_GEN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#include "SymbolTable.hpp"

class CodeContext {
		static unsigned int next_temp;
		static unsigned int next_label;
		static unsigned int next_block;
	
		std::vector<SymbolTable*> storage;
	
	public:
		std::stringstream buffer;
		std::stack<SymbolTable*> blocks;
		SymbolTable* global = NULL;
	
		std::string new_temp();
		std::string new_label();
		void push_block();
		void pop_block();
		SymbolMap& locals() { return blocks.top()->locals; }
		SymbolMap& globals() { return global->locals; }
		std::string printSymbolTable();
};

#endif /* CODE_GEN_HPP */