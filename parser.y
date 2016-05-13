%{
#include <stdio.h>
%}

// Symbols.
%union
{
	char	*sval;
};
%token <sval> IDENTIFIER
%token <sval> NUMBER
%token <sval> STRING
%token MULT
%token RETURNFUNCTION
%token BEGINBLOCK
%token ENDBLOCK
%token BEGINPARENTHESE
%token ENDPARENTHESE
%token PARAMETERSEPARATOR
%token POINTVIRGULE
%token FOR
%token PLUS
%token MINUS
%token NOTEQ
%token GTEQ
%token GT
%token LSEQ
%token LS
%token EQUAL



%start Function
%%


//{ printf("\tPart : %s\n", $1); }
Function:

		FunctionTopStructure
	    FunctionBody
		FunctionBottomStructure

FunctionTopStructure:
	RETURNFUNCTION IDENTIFIER BEGINPARENTHESE ParametersFunction ENDPARENTHESE
  BEGINBLOCK
	;

FunctionBody:
	ForLoop
	//|IfElseCondition FunctionBody
	//|VariableDefinition FunctionBody
	//|VariableManipulation FunctionBody
	;

FunctionBottomStructure:
	ENDBLOCK
	;

ForLoop:
	ForLoopTop
		ForLoopBody
	ForLoopBottom

ForLoopTop:
	ForLoopTopBegin ForLoopTopFirstElement POINTVIRGULE ForTopSecondElement POINTVIRGULE ForTopThirdElement ForLoopTopEnd
	;

ForLoopTopBegin:
	FOR BEGINPARENTHESE
	;

ForLoopTopEnd:
	ENDPARENTHESE
	BEGINBLOCK
	;

ForLoopTopFirstElement:
	IDENTIFIER IDENTIFIER
	;

ForTopSecondElement:
  IDENTIFIER EQUAL IDENTIFIER
  |IDENTIFIER LS IDENTIFIER
  |IDENTIFIER LSEQ IDENTIFIER
  |IDENTIFIER GT IDENTIFIER
  |IDENTIFIER GTEQ IDENTIFIER
  |IDENTIFIER NOTEQ IDENTIFIER
  ;

ForTopThirdElement:
  IDENTIFIER PLUS PLUS
  |PLUS PLUS IDENTIFIER
  |IDENTIFIER MINUS
  |MINUS MINUS IDENTIFIER
  |IDENTIFIER PLUS NUMBER
  |IDENTIFIER MINUS NUMBER
	;

ForLoopBody:
	//TODO
	;

ForLoopBottom:
	ENDBLOCK
	;

ParametersFunction:
  %empty
  | IDENTIFIER Pointer IDENTIFIER PARAMETERSEPARATOR ParametersFunction
  | IDENTIFIER Pointer IDENTIFIER
  ;

Pointer:
  %empty
  |MULT

%%

int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
}
