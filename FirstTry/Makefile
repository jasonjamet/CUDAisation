all:
	bison -t -v -d parser.y -Wall -Wconflicts-rr
	mv parser.tab.h parser.h
	mv parser.tab.c parser.y.c
	flex -d parser.lex
	mv lex.yy.c parser.lex.c
	g++ -g -c parser.lex.c -o parser.lex.o
	g++ -g -c parser.y.c -o parser.y.o
	g++ -g -o parser parser.lex.o parser.y.o -lfl

clean:
	rm *.o *.c parser *.h
