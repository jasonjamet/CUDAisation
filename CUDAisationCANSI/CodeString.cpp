#include "CodeString.hpp"

int CodeString::tabs = -1;

std::string CodeBlock::toPrettyCode(){
	std::stringstream result;
	
	CodeString::tabs++;
	
	for( auto &i : buffer ) {
		result << i->toPrettyCode();
	}
	
	CodeString::tabs--;
	
	return result.str();
}

void CodeBlock::add(CodeString* part){
	buffer.push_back(part);
}

std::string CodeLine::toPrettyCode(){
	int _tabs = CodeString::tabs;
	std::string x = "";
	while(_tabs-- > 0){
		x += "\t";
	}
	return x + buffer.str() + "\n";
}

void CodeLine::add(std::string part){
	buffer << part;
}

void CodeLine::add(CodeString* other){
	CodeLine* pd = dynamic_cast<CodeLine*>(other);
    if (pd==0) {}
	else {
		buffer << pd->buffer.str();	
	}
}
