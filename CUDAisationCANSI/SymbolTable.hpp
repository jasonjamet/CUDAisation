#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <iostream>
#include <map>

class Symbol {
	public: 
		std::string identifier;
		int invocations = 0;
	
		Symbol(std::string identifier) :
		identifier(identifier) {}
	
		std::string toStdString();
		void invoque();
};

typedef std::map<std::string,Symbol*> SymbolMap;

class SymbolTable {
		int context_index;
	public:
		SymbolMap locals;
		SymbolTable(){}
		SymbolTable(int context_index) : context_index(context_index) {}
		~SymbolTable(){}
	
		std::string toStdString();
};

#endif /* SYMBOL_TABLE_HPP */