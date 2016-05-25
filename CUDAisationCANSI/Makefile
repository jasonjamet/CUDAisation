all: parser

parser: lex.yy.cpp ansi-c.tab.cpp main.cpp node.cpp CodeGen.cpp CodeString.cpp SymbolTable.cpp
	g++ -std=c++11 $^ -o $@

lex.yy.cpp: ansi-c.l
	flex  -o $@ $^

ansi-c.tab.cpp: ansi-c.y
	bison -t -v -d $^ -o $@

test: parser
	@./test.sh

clean:
	rm -f ansi-c.tab.cpp ansi-c.tab.hpp lex.yy.cpp parser *.gch
