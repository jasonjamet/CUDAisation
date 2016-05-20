# #!/bin/bash
#
# echo "Parser Tests"
# echo "============"
# echo
#
# function assert {
# 	echo "---- Test ----"
# 	echo
# 	echo $1
# 	echo
# 	echo "Pretty Printing"
# 	echo "---------------"
# 	echo
# 	(echo $1 | PARSE_CODE=TRUE ./parser ) || exit 1
# 	echo
# 	echo "Three Addres Code"
# 	echo "-----------------"
# 	echo
# 	(echo $1 | GENERATE_CODE=TRUE ./parser ) || exit 1
# 	echo
# 	echo "Symbols Table"
# 	echo "-------------"
# 	echo
# 	(echo $1 | PARSE_SYMBOLS=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
# 	echo
# 	echo "Abstract Syntax Tree"
# 	echo "--------------------"
# 	echo
# 	(echo $1 | PARSE_AST=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
# 	echo
# 	echo "---- Done ----"
# 	echo
# }
#
# function assertFile {
# 	echo "---- Test ----"
# 	echo
# 	cat $1
# 	echo
# 	echo "Pretty Printing"
# 	echo "---------------"
# 	echo
# 	(cat $1 | PARSE_CODE=TRUE ./parser ) || exit 1
# 	echo
# 	echo "Three Addres Code"
# 	echo "-----------------"
# 	echo
# 	(cat $1 | GENERATE_CODE=TRUE ./parser ) || exit 1
# 	echo
# 	echo "Symbols Table"
# 	echo "-------------"
# 	echo
# 	(cat $1 | PARSE_SYMBOLS=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
# 	echo
# 	echo "Abstract Syntax Tree"
# 	echo "--------------------"
# 	echo
# 	(cat $1 | PARSE_AST=TRUE ./parser | grep "<.*>" | xmllint --format -) || exit 1
# 	echo
# 	echo "---- Done ----"
# 	echo
# }
#
#
# ## type declaration
# assert "extern static void;"
#
# ## declarations
# assert "int x;"
# assert "float y;"
# assert "int x; int i;"
# assert "int *x;"
# assert "int **x;"
# assert "int x[];"
# assert "int x[5];"
#
# ## assignament
# assert "int x = 1;"
# assert "int x = 1, y = 0;"
# assert "int a = (1+1);"
#
# ## ternary operator
# assert "int a = 1==1?2:3;"
#
# ## binary operation
# assert "int a = 1 + 2;"
# assert "int a = 1 \* 2;"
# assert "int a = 1 \* 2 + 1 \* 3 - 5;"
#
# ## logical operation
# assert "int a = 4 > 20;"
# assert "int x=1<10 && 10==10;"
#
# ## unary operation
# assert "int x = 0; int a = x++;"
# assert "int x = 0; int a = ++x;"
#
# ## function definition
# assert "void f(){}"
# assert "void f(int x){}"
# assert "void f(int x,int y){}"
# assert "void f(){ int x=0; }"
#
# ## SelectionStatement
# assert "int f(){ if(1){}}"
# assert "int f(){ if(1){  } else { } }"
# assert "int f(){ switch(1){ case 1: ; default: ; }}"
#
# ## IterationStatement
# assert "int f(){ int i; while(1) { i++; } }"
# assert "int f(){ int i; do { i++; } while(1);}"
# assert "int f(){ int i; for(i=0; i!=2;) { } }"
# assert "int f(){ int i; for(i=0; i!=2; i++) {return;}}"
#
# ## jump statement
# assert "void f(){ return; }"
# assert "void f(){ break; }"
# assert "int f(){ goto asd; asd: return 0; }"
# assert "int f(){ return 1+1; }"
#
# ## complex programs
# assertFile "tests/simple.c"
# assertFile "tests/if_else.c"
# assertFile "tests/function_call.c"
# assertFile "tests/factorial.c"
#
# echo
# echo "Ok"
# exit 0

PARSE_AST=TRUE ./parser < tests/simple.c  | grep "<.*>"  | xmllint --format -
