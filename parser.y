%{
#include <stdio.h>
#include <string.h>

char gtidName[100];
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
%token PRAGMACUDA
%token THREADLOOP



%start CudaPragma
%%


//{ printf("\tPart : %s\n", $1); }
CudaPragma:
	PRAGMACUDA THREADLOOP BEGINPARENTHESE IDENTIFIER ENDPARENTHESE {strcpy(gtidName, $4);}
	Function
	;


Function:

		FunctionTopStructure
	    FunctionBody
		FunctionBottomStructure
		;


FunctionTopStructure:
	FunctionTopStructureBegin ParametersFunction  FunctionTopStructureEnd
	;

FunctionTopStructureBegin:
	RETURNFUNCTION IDENTIFIER BEGINPARENTHESE { printf("__global__ void %s (", $2); }
	;

FunctionTopStructureEnd:
	ENDPARENTHESE BEGINBLOCK { printf(") {\n\t int %s=((((BlocIdx.x * GridDim.y + BlocIdx.y) * GridDim.z + BlocIdx.z) * BlocDim.x + ThreadIdx.x) * BlocDim.y + ThreadIdx.y) * BlocDim.z + ThreadIdx.z; \n", gtidName); }
	;

FunctionBody:
	ForLoop
	//|IfElseCondition FunctionBody
	//|VariableDefinition FunctionBody
	//|VariableManipulation FunctionBody
	;

FunctionBottomStructure:
	ENDBLOCK	{ printf("\n}"); }
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
	IDENTIFIER IDENTIFIER EQUAL IDENTIFIER
	| IDENTIFIER
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
	%empty
	//TODO
	;

ForLoopBottom:
	ENDBLOCK
	;

FunctionTopElement:
  %empty
  | IDENTIFIER Pointer IDENTIFIER PARAMETERSEPARATOR ParametersFunction
  | IDENTIFIER Pointer IDENTIFIER
  ;

FunctionTopVarWithPointer:
	IDENTIFIER
	|IDENTIFIER Pointer


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
