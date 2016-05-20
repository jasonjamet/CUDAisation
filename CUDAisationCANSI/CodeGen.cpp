#include "CodeGen.hpp"

unsigned int CodeContext::next_temp = 0;
unsigned int CodeContext::next_label = 0;
unsigned int CodeContext::next_block = 0;

std::string CodeContext::new_temp(){
	return "t" + std::to_string(next_temp++);
}

std::string CodeContext::new_label(){
	return "L" + std::to_string(next_label++);
}

void CodeContext::push_block(){
	SymbolTable *t = new SymbolTable(next_block++);
	if(next_block == 1){
		global = t;
	}

	blocks.push(t);
}

void CodeContext::pop_block(){
	SymbolTable *top = blocks.top();
	blocks.pop();
	storage.push_back(top);
}

std::string CodeContext::printSymbolTable(){
	std::string result = "<Contexts>";

	for( auto &i : storage ){
		result += i->toStdString();
	}

	result += "</Contexts>";

	return result;
}
