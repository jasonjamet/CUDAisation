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

typedef struct ThirdElementNode {
	string name;
	string inc;
} ThirdElementNode;

typedef struct ForNode {
	string firstElement;
	string secondElement;
	ThirdElementNode thirdElement;
	string body;
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

ParameterNode tmpParamParsed;
PragmaCUDANode pragmaCUDAParsed;
FunctionNode fncParsed;
ForNode forParsed;

%}

// Symbols.
%union
{
	char	*sval;
};
%token <sval> IDENTIFIER
%token <sval> ALLCHARACTERS
%token <sval> NUMBER
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
	PRAGMACUDA THREADLOOP BEGINPARENTHESE IDENTIFIER ENDPARENTHESE {pragmaCUDAParsed.thread_loop = $4;}
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
	RETURNFUNCTION IDENTIFIER BEGINPARENTHESE { fncParsed.returnParameter = "__global__ void"; fncParsed.name = $2; }
	;

FunctionTopStructureEnd:
	ENDPARENTHESE BEGINBLOCK
	;

FunctionTopElement:
  %empty
  | FunctionTopElementFull PARAMETERSEPARATOR FunctionTopElement
  | FunctionTopElementFull
  ;

FunctionTopElementFull:
	FunctionTopElementTypeAndPointer FunctionTopElementVarNameAndArray { fncParsed.params.push_back(tmpParamParsed); tmpParamParsed.name=""; tmpParamParsed.type="";}
	;

FunctionTopElementTypeAndPointer:
	IDENTIFIER	{tmpParamParsed.type = $1;}
	|IDENTIFIER Pointer {tmpParamParsed.type = $1 + tmpParamParsed.type;}
	;

Pointer:
  MULT {tmpParamParsed.type = " *"; }
;

FunctionTopElementVarNameAndArray:
IDENTIFIER {tmpParamParsed.name = $1;}
|IDENTIFIER FunctionTopElementVarArray {tmpParamParsed.name = $1 + tmpParamParsed.name;} // probleme sur l'ordre des tableau, est ce vraiment utile?
;

FunctionTopElementVarArray:
%empty
|ARRAY FunctionTopElementVarArray {tmpParamParsed.name =tmpParamParsed.name + $1;}
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
	ForLoopTopBegin ALLCHARACTERS POINTVIRGULE ALLCHARACTERS POINTVIRGULE ForTopThirdElement ForLoopTopEnd {forParsed.firstElement = $2; forParsed.secondElement = $4;}
	;

ForLoopTopBegin:
	FOR BEGINPARENTHESE
	;

ForLoopTopEnd:
	ENDPARENTHESE
	BEGINBLOCK
	;

ForTopThirdElement:
  IDENTIFIER PLUS PLUS {forParsed.thirdElement.name = $1; forParsed.thirdElement.inc = "++";}
  |PLUS PLUS IDENTIFIER {forParsed.thirdElement.name = $3; forParsed.thirdElement.inc = "++";}
	;

ForLoopBody:
	%empty
	|ALLCHARACTERS ForLoopBody {forParsed.body+= $1; }
	;

ForLoopBottom:
	ENDBLOCK
	;


%%

int yyerror(char const*s) {
  cout << "yyerror : " << s << endl;
}

string getFormatedFunction() {
	string str;
	for(int i=0; i< fncParsed.params.size(); ++i) {
		str += fncParsed.params[i].type + " " + fncParsed.params[i].name;
		if(i != fncParsed.params.size()-1) {
			str += ", ";
		}
	}
	return str;
}


int main(void) {
  yyparse();
	cout << fncParsed.returnParameter << " " << fncParsed.name << "(" << getFormatedFunction() << ") {" << endl;
	cout << "\t int " << pragmaCUDAParsed.thread_loop << "= ((((BlocIdx.x * GridDim.y + BlocIdx.y) * GridDim.z + BlocIdx.z) * BlocDim.x + ThreadIdx.x) * BlocDim.y + ThreadIdx.y) * BlocDim.z + ThreadIdx.z;" << endl ;
	cout << "\t if(" << forParsed.secondElement << ") {";
	cout << "\t\t " << forParsed.body << endl;
	cout << "\t }" << endl;
	cout << "}" << endl;
}
