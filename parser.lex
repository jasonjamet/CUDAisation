%{

#include "parser.h"




%}

blanks          [ \t\n]+
identifier			[_a-zA-Z0-9]+
string					[a-zA-Z]+
number					[0-9]+
array						\[number\]

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
