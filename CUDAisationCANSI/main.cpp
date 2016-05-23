#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"
#include "CodeGen.hpp"
#include "CodeString.hpp"

/*
 *  _______________________________________
 * / Q: How many IBM CPU's does it take to \
 * | do a logical right shift? A: 33. 1 to |
 * | hold the bits and 32 to push the      |
 * \ register.                             /
 *  ---------------------------------------
 *         \   ^__^
 *          \  (oo)\_______
 *             (__)\       )\/\
 *                 ||----w |
 *                 ||     ||
 */




extern int yyparse();
extern TranslationUnit* root;

bool integrityTest() {
	for(auto &i : cuda_loop_relation_list) {
		std::string thread_loop_identifier;
		std::string for_loop_inc_identifier;

		for(auto cudaParam : i->pragma_cuda->cuda_param_list) {
			if(cudaParam->token == 318) {
				thread_loop_identifier = *(cudaParam->cuda_params_args_list.front()->arg);
			}
		}

		for(auto &j : i->loop_list) {
			for_loop_inc_identifier = "";

			ForCompoundIterationStatement * for_compound = dynamic_cast<ForCompoundIterationStatement *>(j);
			if(for_compound) {
				if(for_compound->expression.size() == 1) {
					PostfixOperation * postfix_operation = dynamic_cast<PostfixOperation *>(for_compound->expression.back());
					UnaryOperation * unary_operation = dynamic_cast<UnaryOperation *>(for_compound->expression.back());
					if(postfix_operation || unary_operation) {
						Identifier * identifier;
						std::string inc_operator;

						if(postfix_operation) {
						 identifier = dynamic_cast<Identifier *>(postfix_operation->operand);
						 inc_operator = postfix_operation->unary_operator->value;
						}
						if(unary_operation) {
							identifier = dynamic_cast<Identifier *>(unary_operation->operand);
							inc_operator = unary_operation->unary_operator->value;
						}
						if(identifier) {
							for_loop_inc_identifier = identifier->value;
						}
						if(inc_operator != "++") {
							std::cout << "Loop found but ignored, inc operator incorect" << std::endl;
						}
					}
				}
			}
			if(thread_loop_identifier == for_loop_inc_identifier) {
				bool identifier_declared = false;
				for(auto &k : i->cuda_variable_list) {
					if(thread_loop_identifier == k) {
						std::cout << "Loop found" << std::endl;
						identifier_declared = true;
					}
				}
				if(identifier_declared) {
					std::cout << "Loop found, but the variable " << thread_loop_identifier << " is not declared" << std::endl;
				}
			} else {
				std::cout << "Loop found but ignored, loop on " << for_loop_inc_identifier << " instead of " << thread_loop_identifier << std::endl;
			}
		}
	}
}

int main(int argc, char **argv) {
	int parse_result = yyparse();
	char *PARSE_CODE = getenv ("PARSE_CODE");
	char *GENERATE_CODE = getenv ("GENERATE_CODE");
	char *PARSE_SYMBOLS = getenv ("PARSE_SYMBOLS");
	char *PARSE_AST = getenv ("PARSE_AST");

	if(parse_result == 0){
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

		if (GENERATE_CODE != NULL){
			/** will generate code */
			CodeContext *context = new CodeContext();
			root->generateCode(context);
			std::cout << context->buffer.str();
		}

		if ( PARSE_SYMBOLS != NULL ){
			CodeContext *context = new CodeContext();
			root->generateCode(context);
			std::cout << context->printSymbolTable();
		}

		integrityTest();
	}

	return parse_result;
}
