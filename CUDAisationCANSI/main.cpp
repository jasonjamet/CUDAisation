#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "node.hpp"
#include "CodeGen.hpp"
#include "CodeString.hpp"
#include "set"
#include "algorithm"


extern FILE *yyin;
extern int yyparse();
extern TranslationUnit* root;



bool checkExtentionFile(char* fileName) {
	if(fileName != NULL) {
		std::string fileNameStr = fileName;
		std::string fileExtention = fileNameStr.substr(fileNameStr.find(".")+1);
		return (fileExtention == "c" || fileExtention == "cpp");
	} else {
		return true;
	}

}

void generateXmlOutput(std::string outputFileName, bool show) {
	if(outputFileName != "") {
		if(outputFileName.find(".") != std::string::npos) {
			FILE *outFile_p;
			outFile_p=fopen(outputFileName.c_str(),"w");
			if(outFile_p == NULL) {
				printf("couldn't open temp for writting\n");
				exit(0);
			} else {
				fputs(root->toStdString().c_str(),outFile_p);
				fclose(outFile_p);
			}
		}
	}
	if(show) {
		std::cout << root->toStdString() << std::endl;
	}
}

void generateCcodeOutput(std::string outputFileName, bool show) {
	CodeBlock *context = new CodeBlock();
	root->toPrettyCode(context);

	if(outputFileName != "") {
		FILE *outFile_p;
		outFile_p=fopen(outputFileName.c_str(),"w");
	  if(outFile_p == NULL) {
	   printf("couldn't open temp for writting\n");
	   exit(0);
	  } else {
			fputs(context->toPrettyCode().c_str(),outFile_p);
			fclose(outFile_p);
		}
	}
	if(show) {
		std::cout << context->toPrettyCode();
	}
}

void help() {
	std::cout	<< "Transforms \"C\" functions to \"CUDA\" functions." << std::endl
	<< "Usage: cudaparse [OPTION] [FILE]" << std::endl
	<< std::endl
	<< "Example: cudaparse main.c" << std::endl
	<< "-x  \t\t Print an XML representation of the tree (build from ANSI-C)." << std::endl
	<< "-c  \t\t Print the C code with cuda kernel(s)." << std::endl
	<< "-o OUTPUT_FILE \t Save the result on a file, depend to the prints options (if none, store the c result)." << std::endl
	<< "-h \t	 Print help informations." << std::endl;

}


int main(int argc, char **argv) {
	int opt = 0;
	bool showXml = false;
	bool showC = false;
	std::string outputFileName = "";


	while ((opt = getopt(argc, argv, "xco:h")) != -1) {
		switch(opt) {
			case 'x':
				showXml = true;
				break;
			case 'c':
				showC = true;
				break;
			case 'o':
				if(optarg == NULL || optarg == argv[argc-1]) {
					std::cout << "Option -o requires an argument. -h for more informations" << std::endl;
					return 1;
				} else {
					std::string outputFileNameStr = optarg;
					if(outputFileNameStr.find("-") != std::string::npos) {
						std::cout << "Option -o requires an argument. -h for more informations" << std::endl;
						return 1;
					}
					outputFileName = optarg;
				}
				break;
			case 'h':
			case '?':
				if (optopt == 'o') {
					fprintf (stderr, "Option -%c requires an argument. -h for more informations\n", optopt);
				}
				else if (isprint (optopt)) {
					fprintf (stderr, "Unknown option `-%c'. -h for more informations\n", optopt);
				}
				help();
				return 1;
			default:
				help();
				return 1;
		}
	}

	if(argc < 2) {
		std::cout << "Please specify an input file" << std::endl;
		return 1;
	} else {
		if(checkExtentionFile(argv[argc-1])) {
			yyin=fopen(argv[argc-1],"r+");
			if(yyin == NULL) {
				std::cout << "Couldn't open file" << std::endl;
				return 1;
			} else {
				if(yyparse() == 0) {
					integrityTest();

					if(showC && showXml && outputFileName != "") {
						generateXmlOutput("", true);
						generateCcodeOutput(outputFileName.c_str(), true);
					} else if(!showC && !showXml && outputFileName == "") {
						generateCcodeOutput("", true);
					} else {
						generateXmlOutput(outputFileName.c_str(), showXml);
						generateCcodeOutput(outputFileName.c_str(), showC);
					}
				} else {
						std::cout << "Error during the parse of the file." << std::endl;
				}
				fclose(yyin);
			}

		} else {
			std::cout << "Please specify a C or C++ input file" << std::endl;
		}
	}

	return 0;
}
