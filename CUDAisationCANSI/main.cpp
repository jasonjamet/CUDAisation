#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"
#include "CodeGen.hpp"
#include "CodeString.hpp"
#include "set"
#include "algorithm"


extern int yyparse();
extern TranslationUnit* root;





int main(int argc, char **argv) {
	int parse_result = yyparse();
	char *PARSE_CODE = getenv ("PARSE_CODE");
	char *PARSE_AST = getenv ("PARSE_AST");

	if(parse_result == 0){
		integrityTest();
  		if (PARSE_AST != NULL){
			/** will print the ast in std string */
			std::cout << root->toStdString() << std::endl;
		}

		if (PARSE_CODE != NULL){
			/** will print pretty code */
			CodeBlock *context = new CodeBlock();
			root->toPrettyCode(context);
			std::cout << context->toPrettyCode();
		}

	}

	return parse_result;
}
