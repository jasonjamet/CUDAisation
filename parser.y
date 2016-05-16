%{
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int yylex(void);
int yyerror(char const*);


typedef struct ParameterNode {
	string type;
	string name;
} ParameterNode;


typedef struct ConditionNode {
	ParameterNode leftValue;
	string comp;
	ParameterNode rightValue;
} ConditionNode;

typedef struct ForNode {
	ParameterNode firstElement;
	ConditionNode condition;
} ForNode;

typedef struct FunctionNode {
	string returnParameter;
	string name;
	vector<ParameterNode> params;
} FunctionNode;

typedef struct PragmaCUDANode {
	string thread_loop;
	vector<ParameterNode> params;
} PragmaCUDANode;

ParameterNode tmpParam;
PragmaCUDANode pragmaCUDA;
FunctionNode fnc;

%}

// Symbols.
%union
{
	char	*sval;
};
%token <sval> IDENTIFIER
%token <sval> NUMBER
%token <sval> STRING
%token <sval> ARRAY
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


CudaPragma:
	PRAGMACUDA THREADLOOP BEGINPARENTHESE IDENTIFIER ENDPARENTHESE {pragmaCUDA.thread_loop = $4;}
	Function
	;


Function:

		FunctionTopStructure
	    FunctionBody
		FunctionBottomStructure
		;


FunctionTopStructure:
	FunctionTopStructureBegin FunctionTopElement  FunctionTopStructureEnd
	;

FunctionTopStructureBegin:
	RETURNFUNCTION IDENTIFIER BEGINPARENTHESE { fnc.returnParameter = "__global__ void"; fnc.name = $2; }
	;

FunctionTopStructureEnd:
	ENDPARENTHESE BEGINBLOCK
	;

FunctionBody:
	ForLoop
	//|IfElseCondition FunctionBody
	//|VariableDefinition FunctionBody
	//|VariableManipulation FunctionBody
	;

FunctionBottomStructure:
	ENDBLOCK	{ cout << endl; }
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
  | FunctionTopElementFull PARAMETERSEPARATOR FunctionTopElement
  | FunctionTopElementFull
  ;

FunctionTopElementFull:
	FunctionTopElementTypeAndPointer FunctionTopElementVarNameAndArray { fnc.params.push_back(tmpParam); }
	;

FunctionTopElementTypeAndPointer:
	IDENTIFIER	{tmpParam.type = $1;}
	|IDENTIFIER Pointer {tmpParam.type = $1;}
	;

Pointer:
  MULT {tmpParam.type += " *"; }
;

FunctionTopElementVarNameAndArray:
IDENTIFIER {tmpParam.name = $1;}
|IDENTIFIER FunctionTopElementVarArray {tmpParam.name = $1;}
;

FunctionTopElementVarArray:
%empty
|ARRAY FunctionTopElementVarArray {tmpParam.name += "[" + (string) $1 + "]";}
;
%%

int yyerror(char const*s) {
  cout << "yyerror : " << s << endl;
}

string getFormatedFunction() {
	string str;
	for(int i=0; i< fnc.params.size(); ++i) {
		str += fnc.params[i].type + " " + fnc.params[i].name;
		if(i != fnc.params.size()-1) {
			str += ", ";
		}
	}
	return str;
}


int main(void) {
  yyparse();
	cout << fnc.returnParameter << " " << fnc.name << "(" << getFormatedFunction() << ")";
	cout << "{\n\t int " << pragmaCUDA.thread_loop << "=((((BlocIdx.x * GridDim.y + BlocIdx.y) * GridDim.z + BlocIdx.z) * BlocDim.x + ThreadIdx.x) * BlocDim.y + ThreadIdx.y) * BlocDim.z + ThreadIdx.z;" << endl << "}" << endl;
}
