%{

#include "parser.h"




%}
blanks          [ \t\n]+
identifier			[a-zA-Z_][a-zA-Z0-9_]*
allcharacters		[a-zA-Z0-9]*
number					[0-9]+
array						\[[0-9]+\]

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


{identifier}	{
				yylval.sval = (char*)malloc(strlen(yytext));
				strncpy(yylval.sval, yytext, strlen(yytext));
				return(IDENTIFIER);
}

{array}	{
				yylval.sval = (char*)malloc(strlen(yytext));
				strncpy(yylval.sval, yytext, strlen(yytext));
				return(ARRAY);
}

{allcharacters}	{
				yylval.sval = (char*)malloc(strlen(yytext));
				strncpy(yylval.sval, yytext, strlen(yytext));
				return(ALLCHARACTERS);
}
