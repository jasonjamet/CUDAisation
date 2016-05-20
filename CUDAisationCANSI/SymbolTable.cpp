#include "SymbolTable.hpp"

std::string Symbol::toStdString(){
	std::string result = "<Symbol>";
	result += "<Identifier>" + identifier + "</Identifier>";
	result += "<Invocations>" + std::to_string(invocations) + "</Invocations>";
	result += "</Symbol>";
	return result;
}

void Symbol::invoque(){
	invocations++;
}

std::string SymbolTable::toStdString(){
	std::string result = "<SymbolTable context='" + std::to_string(context_index) + "'>";
	
	for (auto &symbol : locals) {
		result += symbol.second->toStdString();
	}
	
	result += "</SymbolTable>";
	return result;
}
