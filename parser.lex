%{

#include "parser.h"

%}
blanks          [ \t\n]+
number					[0-9]+
array						\[{number}\]
identifier			[a-zA-Z_][a-zA-Z0-9_]*
allcharacters		.*
%%

{blanks}        { /* ignore */ }

"thread_loop"		return(THREADLOOP);
"#pragma cuda"	return(PRAGMACUDA);
"void"					return(RETURNFUNCTION);
"("							return(BEGINPARENTHESE);
")"							return(ENDPARENTHESE);
"{"							return(BEGINBLOCK);
"}"							return(ENDBLOCK);
","							return(PARAMETERSEPARATOR);
"for"						return(FOR);
";"							return(POINTVIRGULE);
"="   	 			  return(EQUAL);
"<"    	   			return(LS);
"<="   		   		return(LSEQ);
">"    	   			return(GT);
">="   	   			return(GTEQ);
"<>"    	  		return(NOTEQ);
"+"							return(PLUS);
"-"							return(MINUS);
"*"							return(MULT);

{array}	{
				yylval.sval = (char*)malloc(strlen(yytext));
				strncpy(yylval.sval, yytext, strlen(yytext));
				return(ARRAY);
}

{identifier}	{
				yylval.sval = (char*)malloc(strlen(yytext));
				strncpy(yylval.sval, yytext, strlen(yytext));
				return(IDENTIFIER);
}

{allcharacters}	{
				yylval.sval = (char*)malloc(strlen(yytext));
				strncpy(yylval.sval, yytext, strlen(yytext));
				return(ALLCHARACTERS);
}
