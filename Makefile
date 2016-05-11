all:
	bison -d parser.y -Wall
	mv parser.tab.h parser.h
	mv parser.tab.c parser.y.c
	flex parser.lex
	mv lex.yy.c parser.lex.c
	gcc -g -c parser.lex.c -o parser.lex.o
	gcc -g -c parser.y.c -o parser.y.o
	gcc -g -o parser parser.lex.o parser.y.o -lfl

clean:
	rm *.o *.c parser *.h
