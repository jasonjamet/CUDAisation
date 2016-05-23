#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <map>

#include "CodeString.hpp"
#include "CodeGen.hpp"

class Node {
	public:
		virtual ~Node() {}
		virtual std::string toStdString() = 0;
		virtual void toPrettyCode(CodeString*) = 0;
		virtual std::string generateCode(CodeContext*) = 0;
};

class DeclarationSpecifier;

typedef std::vector<DeclarationSpecifier*> DeclarationSpecifierList;

class Expression : public Node {};

typedef std::vector<Expression*> ExpressionList;

class Operator : public Expression {
	public:
		std::string value;

		Operator(std::string value) : value(value) {}
		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class ConstantExpression : public Expression {};

class Identifier : public Expression {
	public:
		std::string value;

		Identifier(std::string value) : value(value){}
		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

typedef std::vector<Identifier*> IdentifierList;

class Constant : public Expression {
	public:
		std::string value;

		Constant(std::string value) : value(value){}
		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class StringLiteral : public Expression {
	public:
		std::string value;

		StringLiteral(std::string value) : value(value){}
		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class PrimaryExpression : public Expression {
	public:
		ExpressionList expression_list;
		PrimaryExpression(ExpressionList expression_list) : expression_list(expression_list) {}

		std::string toStdString();

		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class PostfixOperation : public Expression {
	public:
		Expression *operand = NULL;
		Operator *unary_operator = NULL;

		PostfixOperation(Expression *operand, Operator *unary_operator) :
			operand(operand), unary_operator(unary_operator) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class ArrayAccess : public Expression {
	public:
		Expression *postfix_expression = NULL;
		ExpressionList expression;

		ArrayAccess(Expression *postfix_expression,ExpressionList expression):
			postfix_expression(postfix_expression),
			expression(expression){}

		void toPrettyCode(CodeString*);
		std::string toStdString();
		std::string generateCode(CodeContext*);

};

class FunctionCall : public Expression {
  public:
    Expression *postifx_expression = NULL;
    ExpressionList argument_expression_list;

    FunctionCall(Expression *postifx_expression) : postifx_expression(postifx_expression){}
    FunctionCall(Expression *postifx_expression, ExpressionList argument_expression_list) :
      postifx_expression(postifx_expression),
      argument_expression_list(argument_expression_list) {}

    std::string toStdString();

	void toPrettyCode(CodeString*);
	std::string generateCode(CodeContext*);
};

class UnaryOperation : public Expression {
	public:
		Expression *operand = NULL;
		Operator *unary_operator = NULL;

		UnaryOperation(Expression *operand, Operator *unary_operator) :
			operand(operand), unary_operator(unary_operator) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class BinaryOperation : public Expression {
	public:
		Expression *right_operand = NULL;
		Expression *left_operand = NULL;
		Operator *binary_operator = NULL;

		BinaryOperation(Expression *left_operand, Operator *binary_operator, Expression *right_operand) :
			right_operand(right_operand),
			binary_operator(binary_operator),
			left_operand(left_operand) {}

		virtual std::string toStdString();
		virtual void toPrettyCode(CodeString*);
		virtual std::string generateCode(CodeContext*);
};

class LogicalOperation : public BinaryOperation {
	public:
		LogicalOperation(Expression *left_operand, Operator *binary_operator, Expression *right_operand) :
			BinaryOperation(left_operand,binary_operator,right_operand) {}

		std::string generateCode(CodeContext*);
};

class ConditionalExpression : public Expression {
	public:
		Expression *logical_or_expression = NULL;
		ExpressionList expression;
		Expression *conditional_expression = NULL;

		ConditionalExpression(Expression *logical_or_expression,
							ExpressionList expression,
							Expression *conditional_expression) :
		logical_or_expression(logical_or_expression),
		expression(expression),
		conditional_expression(conditional_expression) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class AssignmentExpression : public Expression {
	public:
		Operator *assignment_operator = NULL;
		Expression *unary_expression = NULL;
		Expression *assignment_expression = NULL;

		AssignmentExpression(Expression *unary_expression,
							 Operator *assignment_operator,
							 Expression *assignment_expression) :
			unary_expression(unary_expression),
			assignment_operator(assignment_operator),
			assignment_expression(assignment_expression) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class Statement : public Node {};

typedef std::vector<Statement*> StatementList;

class TranslationUnit : public Expression {
	public:
		StatementList statements;
		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class DeclarationSpecifier : public Statement {};

class StorageClassSpecifier : public DeclarationSpecifier {
	public:
		int token;
		std::string value;

		StorageClassSpecifier(int token, std::string value)
			: token(token), value(value) { }

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*){ return ""; }
};

class TypeSpecifier : public DeclarationSpecifier {
	public:
		int token;
		std::string value;

		TypeSpecifier(int token, std::string value)
			: token(token), value(value) {}

		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*){ return ""; }
};

class TypeQualifier : public DeclarationSpecifier {
	public:
		int token;
		std::string value;

		TypeQualifier(int token, std::string value)
			: token(token), value(value) {}
		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*){ return ""; }
};

typedef std::vector<TypeQualifier*> TypeQualifierList;

class Declarator : public Statement {};

class DirectDeclarator : public Declarator {};

class IdentifierDeclarator : public DirectDeclarator {
	public:
		std::string identifier;
		IdentifierDeclarator(std::string identifier) : identifier(identifier) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class ArrayDeclarator : public DirectDeclarator {
	public:
		DirectDeclarator *direct_declarator = NULL;
		Expression *constant_expression = NULL;

		ArrayDeclarator(DirectDeclarator *direct_declarator) : direct_declarator(direct_declarator) {}
		ArrayDeclarator(DirectDeclarator *direct_declarator, Expression *constant_expression) :
			direct_declarator(direct_declarator), constant_expression(constant_expression) {}

		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class ParameterDeclaration : public Statement {
	public:
		DeclarationSpecifierList declaration_specifiers;
		Declarator *declarator = NULL;

		ParameterDeclaration(DeclarationSpecifierList declaration_specifiers, Declarator *declarator) :
			declaration_specifiers(declaration_specifiers), declarator(declarator) {}

		ParameterDeclaration(DeclarationSpecifierList declaration_specifiers) :
			declaration_specifiers(declaration_specifiers) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

typedef std::vector<ParameterDeclaration*> ParameterDeclarationList;

class FunctionDeclarator : public DirectDeclarator {
	public:
		DirectDeclarator *direct_declarator = NULL;
		IdentifierList identifier_list;
		ParameterDeclarationList parameter_type_list;

		FunctionDeclarator(DirectDeclarator *direct_declarator) :
			direct_declarator(direct_declarator) {}

		FunctionDeclarator(DirectDeclarator *direct_declarator, IdentifierList identifier_list) :
			direct_declarator(direct_declarator), identifier_list(identifier_list) {}

		FunctionDeclarator(DirectDeclarator *direct_declarator, ParameterDeclarationList parameter_type_list) :
			direct_declarator(direct_declarator), parameter_type_list(parameter_type_list) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class Pointer : public Statement {
	public:
		TypeQualifierList type_qualifier_list;
		Pointer *child = NULL;

		Pointer() {}

		Pointer(Pointer *child) : child(child) {}

		Pointer(TypeQualifierList type_qualifier_list) : type_qualifier_list(type_qualifier_list) {}

		Pointer(TypeQualifierList type_qualifier_list, Pointer *child) :
			child(child), type_qualifier_list(type_qualifier_list) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class PointerDeclarator : public DirectDeclarator {
	public:
		Pointer *pointer = NULL;
		DirectDeclarator *direct_declarator = NULL;

		PointerDeclarator(DirectDeclarator *direct_declarator) :
			direct_declarator(direct_declarator){
		}

		PointerDeclarator(Pointer *pointer, DirectDeclarator *direct_declarator) :
			pointer(pointer), direct_declarator(direct_declarator){}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class NestedDeclarator : public DirectDeclarator {
	public:
		Declarator *declarator = NULL;

		NestedDeclarator(Declarator *declarator) : declarator(declarator) {}

		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class Initializer : public Statement {
	public:
		Expression *assignment_expression = NULL;

		Initializer(Expression *assignment_expression) :
			assignment_expression(assignment_expression) {}
		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class InitDeclarator : public Statement {
	public:
		Declarator *declarator = NULL;
		Initializer *initializer = NULL;

		InitDeclarator(Declarator *declarator) : declarator(declarator) {}
		InitDeclarator(Declarator *declarator, Initializer *initializer) :
			declarator(declarator),
			initializer(initializer) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

typedef std::vector<InitDeclarator*> InitDeclaratorList;

class Declaration : public Statement {
	public:
		DeclarationSpecifierList declaration_specifiers;
		InitDeclaratorList init_declarator_list;

		Declaration(DeclarationSpecifierList declaration_specifiers) :
			declaration_specifiers(declaration_specifiers) {}

		Declaration(DeclarationSpecifierList declaration_specifiers, InitDeclaratorList init_declarator_list) :
			declaration_specifiers(declaration_specifiers), init_declarator_list(init_declarator_list) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

typedef std::vector<Declaration*> DeclarationList;

class LabeledStatement : public Statement {};

class CaseStatement : public LabeledStatement {
	public:
		Expression *constant_expression = NULL;
		Statement *statement = NULL;

		CaseStatement(Expression *constant_expression, Statement *statement) :
			constant_expression(constant_expression),
			statement(statement) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class DefaultStatement : public LabeledStatement {
	public:
		Statement *statement = NULL;

		DefaultStatement(Statement *statement) :
			statement(statement) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class TaggedStatement : public LabeledStatement {
	public:
		std::string identifier;
		Statement *statement = NULL;

		TaggedStatement(std::string identifier, Statement *statement) :
			identifier(identifier),
			statement(statement) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class CompoundStatement : public Statement {
	public:
		StatementList statement_list;
		DeclarationList declaration_list;

		CompoundStatement(){}

		CompoundStatement(StatementList statement_list) : statement_list(statement_list) {}

		CompoundStatement(DeclarationList declaration_list) : declaration_list(declaration_list) {}

		CompoundStatement(DeclarationList declaration_list, StatementList statement_list) :
			statement_list(statement_list), declaration_list(declaration_list) {}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class ExpressionStatement : public Statement {
	public:
		ExpressionList expression_list;

		ExpressionStatement(ExpressionList expression_list) :
			expression_list(expression_list) {}

        ExpressionStatement(){}

		std::string toStdString();

		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class SelectionStatement : public Statement {

};

class IfSelectionStatement : public SelectionStatement {
	public:

		int token;
		Statement *statement = NULL;
		ExpressionList expression;

		IfSelectionStatement(int token, ExpressionList expression, Statement *statement) :
			token(token),
			expression(expression),
			statement(statement) {}


		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class IfElseSelectionStatement : public SelectionStatement {
	public:
		int token, token_else;
		Statement *statement = NULL, *statement_else = NULL;
		ExpressionList expression;

		IfElseSelectionStatement(int token, ExpressionList expression, Statement *statement, int token_else, Statement *statement_else) :
			token(token),
			expression(expression),
			statement(statement),
			token_else(token_else),
			statement_else(statement_else) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class SwitchSelectionStatement : public SelectionStatement {
	public:
		int token;
		Statement *statement = NULL;
		ExpressionList expression;

		SwitchSelectionStatement(int token, ExpressionList expression, Statement *statement) :
			token(token),
			expression(expression),
			statement(statement) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class IterationStatement : public Statement {};

class WhileIterationStatement : public IterationStatement {
	public:
		int token;
		ExpressionList expression;
		Statement *statement = NULL;

		WhileIterationStatement(int token, ExpressionList expression, Statement *statement) :
			token(token),
			expression(expression),
			statement(statement) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class DoWhileIterationStatement : public IterationStatement {
	public:
		int token, token_while;
		Statement *statement = NULL;
		ExpressionList expression;

		DoWhileIterationStatement(int token, Statement *statement, int token_while, ExpressionList expression) :
			token(token),
			statement(statement),
			token_while(token_while),
			expression(expression) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};


class CudaParamArgs : public Node {
	public:
		std::string* arg;
		CudaParamArgs(std::string *arg) : arg(arg) {

		}
		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

typedef std::vector<CudaParamArgs*> CudaParamArgsList;

class CudaParam : public Node {
	public:
		int token; //Parameter name
		CudaParamArgsList cuda_params_args_list;
		CudaParam(int token, CudaParamArgsList cuda_params_args_list) : token(token), cuda_params_args_list(cuda_params_args_list) {

		}
		CudaParam(int token, CudaParamArgs *cuda_params_args) : token(token) {
			cuda_params_args_list.push_back(cuda_params_args);
		}
		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

typedef std::vector<CudaParam*> CudaParamList;


class PragmaCuda : public Node {
	public:
	int token1;
	int token2;
	CudaParamList cuda_param_list;

	PragmaCuda(int token1, int token2, CudaParamList cuda_param_list) :token1(token1), token2(token2), cuda_param_list(cuda_param_list) {

	}

	std::string toStdString();
	std::string generateCode(CodeContext*);
	void toPrettyCode(CodeString*);
};




class ForSimpleIterationStatement : public IterationStatement {
	public:
		int token;
		ExpressionStatement *expression_statement1, *expression_statement2;
		Statement *statement = NULL;

		ForSimpleIterationStatement(int token, ExpressionStatement *expression_statement1, ExpressionStatement *expression_statement2, Statement *statement) :
			token(token),
			expression_statement1(expression_statement1),
			expression_statement2(expression_statement2),
			statement(statement) {}
		bool isCudaLoop;
		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class ForCompoundIterationStatement : public IterationStatement {
	public:
		int token;
		ExpressionStatement *expression_statement1, *expression_statement2;
		ExpressionList expression;
		Statement *statement = NULL;

		ForCompoundIterationStatement(int token, ExpressionStatement *expression_statement1, ExpressionStatement *expression_statement2,
			ExpressionList expression, Statement *statement) :
			token(token),
			expression_statement1(expression_statement1),
			expression_statement2(expression_statement2),
			expression(expression),
			statement(statement) {}

		std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class JumpStatement : public Statement {
	public:
		int token;
		std::string identifier;
		ExpressionList expression_list;

		JumpStatement(int token) : token(token) {}
		JumpStatement(int token, std::string identifier) :
			token(token),
			identifier(identifier){}
		JumpStatement(int token, ExpressionList expression_list) :
			token(token),
			expression_list(expression_list) {}

		virtual std::string toStdString();
		std::string generateCode(CodeContext*);
		void toPrettyCode(CodeString*);
};

class FunctionDefinition : public Statement {
	public:
		DeclarationSpecifierList declaration_specifier_list;
		Declarator *declarator = NULL;
		DeclarationList declaration_list;
		CompoundStatement *compound_statement = NULL;

		FunctionDefinition(DeclarationSpecifierList declaration_specifier_list, Declarator *declarator, DeclarationList declaration_list, CompoundStatement *compound_statement) :
			declaration_specifier_list(declaration_specifier_list),
			declarator(declarator),
			declaration_list(declaration_list),
			compound_statement(compound_statement) {}

		FunctionDefinition(Declarator *declarator, CompoundStatement *compound_statement) :
			declarator(declarator), compound_statement(compound_statement) {}

		FunctionDefinition(Declarator *declarator, DeclarationList declaration_list, CompoundStatement *compound_statement) :
			declarator(declarator), declaration_list(declaration_list), compound_statement(compound_statement) {}

		FunctionDefinition(DeclarationSpecifierList declaration_specifier_list, Declarator *declarator, CompoundStatement *compound_statement) :
			declaration_specifier_list(declaration_specifier_list), declarator(declarator), compound_statement(compound_statement) {}



		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};

class CudaDefinition : public Statement {
	public:
		PragmaCuda *pragma_cuda;
		FunctionDefinition *functionDefinition;
		CudaDefinition(PragmaCuda *pragma_cuda, FunctionDefinition *functionDefinition) : pragma_cuda(pragma_cuda), functionDefinition(functionDefinition) {
			isACudaFunction();
		}

		void isACudaFunction();

		std::string toStdString();
		void toPrettyCode(CodeString*);
		std::string generateCode(CodeContext*);
};


#endif /* NODE_HPP */
