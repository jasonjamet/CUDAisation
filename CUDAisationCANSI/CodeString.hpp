#ifndef CODE_STRING_HPP
#define CODE_STRING_HPP

#include <iostream>
#include <vector>
#include <sstream>

class CodeString {
	public:
		static int tabs;
		virtual std::string toPrettyCode() = 0;
		virtual void add(CodeString*){}
		virtual void add(std::string){}
};

typedef std::vector<CodeString*> CodeStringList;

class CodeBlock : public CodeString {
	public:
		CodeStringList buffer;
		CodeBlock() {}
		
		void add(CodeString*);
		std::string toPrettyCode();
};

class CodeLine : public CodeString {
	public:
		std::stringstream buffer;
		CodeLine() {}
		CodeLine(std::string text) { buffer << text; }
	
		void add(std::string text);
		void add(CodeString*);
		std::string toPrettyCode();
};
#endif /* CODE_STRING_HPP */