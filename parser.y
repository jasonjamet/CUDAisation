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



Function:
  RETURNFUNCTION IDENTIFIER BEGINPARENTHESE ParametersFunction ENDPARENTHESE
  BEGINBLOCK
    FOR BEGINPARENTHESE IDENTIFIER IDENTIFIER POINTVIRGULE ForCondition POINTVIRGULE ForInc ENDPARENTHESE
    BEGINBLOCK

    ENDBLOCK
  ENDBLOCK
  ;

ForCondition:
  IDENTIFIER EQUAL IDENTIFIER
  |IDENTIFIER LS IDENTIFIER
  |IDENTIFIER LSEQ IDENTIFIER
  |IDENTIFIER GT IDENTIFIER
  |IDENTIFIER GTEQ IDENTIFIER
  |IDENTIFIER NOTEQ IDENTIFIER
  ;

ForInc:
  IDENTIFIER PLUS PLUS
  |PLUS PLUS IDENTIFIER
  |IDENTIFIER MINUS
  |MINUS MINUS IDENTIFIER
  |IDENTIFIER PLUS NUMBER
  |IDENTIFIER MINUS NUMBER

ParametersFunction:
  %empty
  | IDENTIFIER Pointer IDENTIFIER PARAMETERSEPARATOR ParametersFunction
  | IDENTIFIER Pointer IDENTIFIER
  ;

Pointer:
  %empty
  |MULT

/*Parts:
	| Parts Part
	;

Part:
	IDENTIFIER BEGINBLOCK { printf("\tPart : %s\n", $1); }
		Keywords
	ENDBLOCK
	;

Keywords:
	| Keywords Keyword
	;

Keyword:
	IDENTIFIER { printf("\t\tKeyword : %s\n", $1); }
	;*/
%%

int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
}
