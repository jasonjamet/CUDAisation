#include <stdio.h>
#include <stdlib.h>
// #include <iostream>
// #include <unistd.h>
#include "node.hpp"
#include "CodeGen.hpp"
#include "CodeString.hpp"
#include "set"
#include "algorithm"


// extern FILE *yyin;
extern int yyparse();
extern TranslationUnit* root;


//
// bool checkExtentionFile(char* fileName) {
// 	if(fileName != NULL) {
// 		std::string fileNameStr = fileName;
// 		std::string fileExtention = fileNameStr.substr(fileNameStr.find(".")+1);
// 		return (fileExtention == "c" || fileExtention == "cpp");
// 	} else {
// 		return true;
// 	}
//
// }
//
// void generateXmlOutput(char *outputFileName, char *inputFileName) {
// 	if(outputFileName && outputFileName != inputFileName) {
// 		std::string outputFileNameStr = outputFileName;
// 		if(outputFileNameStr.find(".") != std::string::npos) {
// 			FILE *outFile_p;
// 			outFile_p=fopen(outputFileName,"w");
// 			if(!outFile_p) {
// 				printf("couldn't open temp for writting\n");
// 				exit(0);
// 			} else {
// 				fputs(root->toStdString().c_str(),outFile_p);
// 				fclose(outFile_p);
// 			}
// 		}
// 	}
// 	std::cout << root->toStdString() << std::endl;
// }
//
// void generateCcodeOutput(char *outputFileName, char *inputFileName) {
// 	CodeBlock *context = new CodeBlock();
// 	root->toPrettyCode(context);
//
// 	if(outputFileName && outputFileName != inputFileName) {
// 		std::string outputFileNameStr = outputFileName;
// 		if(outputFileNameStr.find(".") != std::string::npos) {
//
// 			FILE *outFile_p;
// 			outFile_p=fopen(outputFileName,"w");
// 		  if(!outFile_p) {
// 		   printf("couldn't open temp for writting\n");
// 		   exit(0);
// 		  } else {
// 				fputs(context->toPrettyCode().c_str(),outFile_p);
// 				fclose(outFile_p);
// 			}
// 		}
// 	}
// 	std::cout << context->toPrettyCode();
// }

int main(int argc, char **argv) {
	// int opt = 0;
	// if(argc < 2) {
	// 	std::cout << "Please specify an input file" << std::endl;
	// 	return 1;
	// } else {
	// 	if(checkExtentionFile(argv[argc-1])) {
	// 		yyin=fopen(argv[argc-1],"r");
	// 		if(!yyin) {
	// 			std::cout << "Couldn't open file" << std::endl;
	// 			return 1;
	// 		} else {
	// 			if(yyparse()) {
	// 				integrityTest();
	// 				while ((opt = getopt(argc, argv, "x:c:")) != -1) {
	// 					switch(opt) {
	// 						case 'x':
	// 							generateXmlOutput(optarg, argv[argc-1]);
	// 							break;
	// 						case 'c':
	// 							generateCcodeOutput(optarg, argv[argc-1]);
	// 							break;
	// 						case '?':
	// 						if (optopt == 'i') {
	// 							printf("\nMissing mandatory input option");
	// 						} else if (optopt == 'o') {
	// 							 printf("\nMissing mandatory output option");
	// 						} else {
	// 							 printf("\nInvalid option received");
	// 						}
	// 						break;
	// 					}
	//
	// 				}
	// 			} else {
	// 					std::cout << "[FAIL] Error during the parse of the file." << std::endl;
	// 			}
	// 			fclose(yyin);
	// 		}
	//
	// 	} else {
	// 		std::cout << "Please specify a C or C++ input file" << std::endl;
	// 	}
	// }

	//yyin=fopen("tests/simple.c","r");
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
