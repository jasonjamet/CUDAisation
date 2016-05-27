#include "node.hpp"
#include "ansi-c.tab.hpp"
#include "set"
#include "algorithm"


std::vector<CudaLoopRelation*> cuda_loop_relation_list;
std::vector<IterationStatement*> loop_list_tmp;
std::vector<IdentifierDeclarator*> cuda_variable_declared_list_tmp;
std::vector<std::string> cuda_variable_used_list_tmp;

bool point_virgule = true;

bool boole = true;

std::string TranslationUnit::toStdString(){
	std::string result = "<TranslationUnit>";

	/** Get childs std strings */
	if(statements.size() != 0){
		result += "<StatementList>";
		for ( auto &i : statements) {
			result += i->toStdString();
		}
		result += "</StatementList>";
	}
	result += "</TranslationUnit>";

	return result;
}

void TranslationUnit::toPrettyCode(CodeString* context){
	/** Get childs std strings */
	if(statements.size() != 0){
		for ( auto &i : statements) {
			i->toPrettyCode(context);
		}
	}
}


std::string StorageClassSpecifier::toStdString(){
	std::string result = "<StorageClassSpecifier>" + value + "</StorageClassSpecifier>";
	return result;
}

void StorageClassSpecifier::toPrettyCode(CodeString *context){
	context->add(value);
}

std::string TypeSpecifier::toStdString(){
	std::string result = "<TypeSpecifier>" + value + "</TypeSpecifier>";
	return result;
}

void TypeSpecifier::toPrettyCode(CodeString* context){
	context->add(value);
}

std::string TypeQualifier::toStdString(){
	std::string result = "<TypeQualifier>" + value + "</TypeQualifier>";
	return result;
}

void TypeQualifier::toPrettyCode(CodeString* context){
	context->add(value);
}

std::string PointerDeclarator::toStdString(){
	std::string result = "<PointerDeclarator>";

	if(pointer != NULL){
		result += pointer->toStdString();
	}

	if(direct_declarator != NULL){
		result += direct_declarator->toStdString();
	}

	result += "</PointerDeclarator>";

	return result;
}

void PointerDeclarator::toPrettyCode(CodeString* context){

	if(pointer != NULL){
		pointer->toPrettyCode(context);
	}

	if(direct_declarator != NULL){
		direct_declarator->toPrettyCode(context);
	}
}


std::string IdentifierDeclarator::toStdString(){
	std::string result = "<IdentifierDeclarator>";
	result += identifier;
	result += "</IdentifierDeclarator>";

	return result;
}

void IdentifierDeclarator::toPrettyCode(CodeString* context){
	context->add(identifier);
	if (isGtid && cuda_loop_relation_list.size() != 0) {
		for (CudaLoopRelation* &i : cuda_loop_relation_list)
		{
			if (i->thread_loop_identifier == identifier) {
				context->add(" = ((((blockIdx.x * gridDim.y + blockIdx.y) * gridDim.z + blockIdx.z) * blockDim.x + threadIdx.x) * blockDim.y + threadIdx.y) * blockDim.z + threadIdx.z");
			}
		}
	}
}



std::string Identifier::toStdString(){
	std::string result = "<Identifier value='" + value + "'></Identifier>";
	return result;
}

void Identifier::toPrettyCode(CodeString* context){
	context->add(value);
}


std::string Operator::toStdString(){

	std::string result = "<Operator>";

	std::stringstream dst;
    for (char ch : value) {
        switch (ch) {
            case '&': dst << "&amp;"; break;
            case '\'': dst << "&apos;"; break;
            case '"': dst << "&quot;"; break;
            case '<': dst << "&lt;"; break;
            case '>': dst << "&gt;"; break;
            default: dst << ch; break;
        }
    }

	result += dst.str();

	result += "</Operator>";
	return result;
}

void Operator::toPrettyCode(CodeString* context){
	context->add(value);
}


std::string Constant::toStdString(){
	std::string result = "<Constant value='" + value + "'></Constant>";
	return result;
}

void Constant::toPrettyCode(CodeString* context){
	context->add(value);
}


std::string StringLiteral::toStdString(){
	std::string result = "<StringLiteral value='" + value + "'></StringLiteral>";
	return result;
}

void StringLiteral::toPrettyCode(CodeString* context){
	context->add(value);
}


std::string PrimaryExpression::toStdString(){
    std::string result = "<PrimaryExpression>";

	if(expression_list.size() != 0){
		result += "<ExpressionList>";
		for( auto &i : expression_list ){
			result += i->toStdString();
		}
		result += "</ExpressionList>";
	}

    result += "</PrimaryExpression>";

    return result;
}

void PrimaryExpression::toPrettyCode(CodeString* context){
	context->add("(");
	if(expression_list.size() != 0){
		for( auto &i : expression_list ){
			i->toPrettyCode(context);
		}
	}
    context->add(")");
}


std::string PostfixOperation::toStdString(){
    std::string result = "<PostfixOperation>";

    if(operand != NULL){
        result += operand->toStdString();
    }

	if(unary_operator != NULL){
		result += unary_operator->toStdString();
	}

    result += "</PostfixOperation>";
    return result;
}

void PostfixOperation::toPrettyCode(CodeString* context){
    if(operand != NULL){
        operand->toPrettyCode(context);
    }

	if(unary_operator != NULL){
		unary_operator->toPrettyCode(context);
	}
}


std::string ArrayAccess::toStdString(){
	std::string result = "<ArrayAccess>";

	if(postfix_expression != NULL){
		result += postfix_expression->toStdString();
	}

	if(expression.size() != 0){
		result += "<ExpressionList>";
		for( auto &i : expression){
			result += i->toStdString();
		}
		result += "</ExpressionList>";
	}

	result += "</ArrayAccess>";
	return result;
}

void ArrayAccess::toPrettyCode(CodeString* context){

	if(postfix_expression != NULL){
		postfix_expression->toPrettyCode(context);
	}

	if(expression.size() != 0){
		context->add("[");
		for( auto &i : expression){
			i->toPrettyCode(context);
		}
		context->add("]");
	} else {
		context->add("[]");
	}
}


std::string FunctionCall::toStdString(){
  std::string result = "<FunctionCall>";

  if(postifx_expression != NULL){
      result += postifx_expression->toStdString();
  }

  if(argument_expression_list.size() != 0){
	  result += "<ArgumentExpressionList>";
	  for( auto &i : argument_expression_list){
		  result += i->toStdString();
	  }
	  result += "</ArgumentExpressionList>";
  }

  result += "</FunctionCall>";
  return result;
}

void FunctionCall::toPrettyCode(CodeString* context){

	if(postifx_expression != NULL){
		postifx_expression->toPrettyCode(context);
	}

	if(argument_expression_list.size() != 0){
		context->add("(");
		int size = argument_expression_list.size();
		for( auto &i : argument_expression_list){
			i->toPrettyCode(context);
			context->add(--size == 0 ? "":", ");
		}
		context->add(")");
	}
	else {
		context->add("()");
	}
}


std::string UnaryOperation::toStdString(){
    std::string result = "<UnaryOperation>";

	if(unary_operator != NULL){
		result += unary_operator->toStdString();
	}

    if(operand != NULL){
        result += operand->toStdString();
    }

    result += "</UnaryOperation>";
    return result;
}

void UnaryOperation::toPrettyCode(CodeString* context){

	if(unary_operator != NULL){
		unary_operator->toPrettyCode(context);
	}

    if(operand != NULL){
        operand->toPrettyCode(context);
    }

}


std::string BinaryOperation::toStdString(){
    std::string result = "<BinaryOperation>";

    if(left_operand != NULL){
        result += left_operand->toStdString();
    }

	if(binary_operator != NULL){
		result += binary_operator->toStdString();
	}

    if(right_operand != NULL){
        result += right_operand->toStdString();
    }

    result += "</BinaryOperation>";
    return result;
}

void BinaryOperation::toPrettyCode(CodeString *context){

    if(left_operand != NULL){
        left_operand->toPrettyCode(context);
    }

	if(binary_operator != NULL){
		context->add(" ");
		binary_operator->toPrettyCode(context);
	}

    if(right_operand != NULL){
		context->add(" ");
        right_operand->toPrettyCode(context);
    }
}


std::string ConditionalExpression::toStdString(){
    std::string result = "<ConditionalExpression>";

    if(logical_or_expression != NULL){
        result += logical_or_expression->toStdString();
    }

    if(expression.size() != 0){
        result += "<ExpressionList>";
        for( auto &i : expression ) {
            result += i->toStdString();
        }
        result += "</ExpressionList>";
    }

    if(conditional_expression != NULL){
        result += conditional_expression->toStdString();
    }

    result += "</ConditionalExpression>";
    return result;
}

void ConditionalExpression::toPrettyCode(CodeString* context){

    if(logical_or_expression != NULL){
        logical_or_expression->toPrettyCode(context);
		context->add(" ?");
    }

    if(expression.size() != 0){
        context->add(" ");
        for( auto &i : expression ) {
            i->toPrettyCode(context);
        }
        context->add(" :");
    }

    if(conditional_expression != NULL){
		context->add(" ");
        conditional_expression->toPrettyCode(context);
    }
}


std::string AssignmentExpression::toStdString(){
  std::string result = "<AssignmentExpression>";

  if(unary_expression != NULL){
    result += unary_expression->toStdString();
  }

  if(assignment_operator != NULL){
    result += assignment_operator->toStdString();
  }

  if(assignment_expression != NULL){
    result += assignment_expression->toStdString();
  }

  result += "</AssignmentExpression>";
  return result;
}

void AssignmentExpression::toPrettyCode(CodeString* context){

	if(unary_expression != NULL){
		unary_expression->toPrettyCode(context);
	}

	if(assignment_operator != NULL){
		context->add(" ");
		assignment_operator->toPrettyCode(context);
	}

	if(assignment_expression != NULL){
		context->add(" ");
		assignment_expression->toPrettyCode(context);
	}
}

std::string ArrayDeclarator::toStdString(){
	std::string result = "<ArrayDeclarator>";

	if(direct_declarator != NULL){
		result += direct_declarator->toStdString();
	}

	if(constant_expression != NULL){
		result += constant_expression->toStdString();
	}

	result += "</ArrayDeclarator>";
	return result;
}

void ArrayDeclarator::toPrettyCode(CodeString* context){
	if(direct_declarator != NULL){
		direct_declarator->toPrettyCode(context);
	}

	context->add("[");

	if(constant_expression != NULL){
		constant_expression->toPrettyCode(context);
	}

	context->add("]");
}



std::string FunctionDeclarator::toStdString(){
	std::string result = "<FunctionDeclarator>";

	if(direct_declarator != NULL){
		result += direct_declarator->toStdString();
	}

	/** Get specifiers childs std strings */
	if(identifier_list.size() != 0) {
		result += "<IdentifierList>";
		for ( auto &i : identifier_list) {
			result += i->toStdString();
		}
		result += "</IdentifierList>";
	}

	if(parameter_type_list.size() != 0){
		result += "<ParameterDeclarationList>";
		for ( auto &i : parameter_type_list) {
			result += i->toStdString();
		}
		result += "</ParameterDeclarationList>";
	}

	result += "</FunctionDeclarator>";
	return result;
}

void FunctionDeclarator::toPrettyCode(CodeString* context){

	if(direct_declarator != NULL){
		direct_declarator->toPrettyCode(context);
	}

	context->add("(");
	if(parameter_type_list.size() != 0){
		int size = parameter_type_list.size();
		for ( auto &i : parameter_type_list) {
			i->declarator->toPrettyCode(context);
			i->toPrettyCode(context);
			context->add(--size == 0? "":", ");
		}
	}

	/** Get specifiers childs std strings */
	if(identifier_list.size() != 0) {
		for ( auto &i : identifier_list) {
			i->toPrettyCode(context);
		}
	}
	context->add(")");
}



std::string NestedDeclarator::toStdString(){
	std::string result = "<NestedDeclarator>";

	if(declarator != NULL){
		result += declarator->toStdString();
	}

	result += "</NestedDeclarator>";
	return result;
}

void NestedDeclarator::toPrettyCode(CodeString* context){
	context->add("(");

	if(declarator != NULL){
		declarator->toPrettyCode(context);
	}

	context->add(")");
}


std::string Pointer::toStdString(){
	std::string result = "<Pointer>";

	if(child){
		result += child->toStdString();
	}

	/** Get specifiers childs std strings */
	if(type_qualifier_list.size() != 0){
		result += "<TypeQualifierList>";
		for ( auto &i : type_qualifier_list) {
			result += i->toStdString();
		}
		result += "</TypeQualifierList>";
	}
	result += "*";

	result += "</Pointer>";

	return result;
}

void Pointer::toPrettyCode(CodeString* context){

	context->add("*");

	if(child){
		child->toPrettyCode(context);
	}

	/** Get specifiers childs std strings */
	if(type_qualifier_list.size() != 0){
		for ( auto &i : type_qualifier_list) {
			i->toPrettyCode(context);
		}
	}

}


std::string InitDeclarator::toStdString(){
	std::string result = "<InitDeclarator>";

	if(declarator != NULL){
		result += declarator->toStdString();
	}

	if(initializer != NULL){
		result += initializer->toStdString();
	}

	result += "</InitDeclarator>";

	return result;
}

void InitDeclarator::toPrettyCode(CodeString* context){
	if(declarator != NULL){
		declarator->toPrettyCode(context);
	}

	if(initializer != NULL){
		context->add(" = ");
		initializer->toPrettyCode(context);
	}
}


std::string Initializer::toStdString(){
    std::string result = "<Initializer>";

    if(assignment_expression != NULL){
        result += assignment_expression->toStdString();
    }

    result += "</Initializer>";

    return result;
}

void Initializer::toPrettyCode(CodeString* context){

    if(assignment_expression != NULL){
        assignment_expression->toPrettyCode(context);
    }
}

std::string Declaration::toStdString(){
	std::string result = "<Declaration>";

	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		result += "<DeclarationSpecifierList>";
		for ( auto &i : declaration_specifiers ) {
			result += i->toStdString();
		}
		result += "</DeclarationSpecifierList>";
	}

	/** Get specifiers childs std strings */
	if(init_declarator_list.size() != 0){
		result += "<InitDeclaratorList>";
		for( auto &i : init_declarator_list ) {
			result += i->toStdString();
		}
		result += "</InitDeclaratorList>";
	}

	result += "</Declaration>";

	return result;
}

void Declaration::toPrettyCode(CodeString *context){
	CodeLine *line = new CodeLine();



	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		int size = declaration_specifiers.size();
		for ( auto &i : declaration_specifiers ) {
			i->toPrettyCode(line);
			line->add(--size == 0? "":" ");
		}
	}

	/** Get specifiers childs std stringqs */
	if(init_declarator_list.size() != 0){
		int size = init_declarator_list.size();
		for( auto &i : init_declarator_list ) {
			line->add(" ");
			i->toPrettyCode(line);
			line->add(--size == 0? "":",");
		}
	}

	line->add(";");
	context->add(line);
};


std::string ParameterDeclaration::toStdString(){
	std::string result = "<ParameterDeclaration>";

	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		result += "<DeclarationSpecifierList>";
		for( auto &i : declaration_specifiers ) {
			result += i->toStdString();
		}
		result += "</DeclarationSpecifierList>";
	}

	if(declarator != NULL){
		result += declarator->toStdString();
	}

	result += "</ParameterDeclaration>";

	return result;
}

void ParameterDeclaration::toPrettyCode(CodeString* context){

	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		int size = declaration_specifiers.size();
		for( auto &i : declaration_specifiers ) {
			i->toPrettyCode(context);
			context->add(--size == 0? "" : " ");
		}
	}

	if(declarator != NULL){
		context->add(" ");
		declarator->toPrettyCode(context);
	}
}


std::string CaseStatement::toStdString(){
	std::string result = "<CaseStatement>";

	if(constant_expression != NULL){
		result += constant_expression->toStdString();
	}

	if(statement != NULL){
		result += statement->toStdString();
	}

	result += "</CaseStatement>";
	return result;
}

void CaseStatement::toPrettyCode(CodeString* context){
	CodeLine* line = new CodeLine("case");

	if(constant_expression != NULL){
		line->add(" ");
		constant_expression->toPrettyCode(line);
		line->add(":");
	}

	context->add(line);

	if(statement != NULL){
		statement->toPrettyCode(context);
	}
}


std::string DefaultStatement::toStdString(){
	std::string result = "<DefaultStatement>";

	if(statement != NULL){
		result += statement->toStdString();
	}

	result += "</DefaultStatement>";
	return result;
}

void DefaultStatement::toPrettyCode(CodeString* context){
	CodeLine* line = new CodeLine("default:");
	context->add(line);

	if(statement != NULL){
		statement->toPrettyCode(context);
	}
}


std::string TaggedStatement::toStdString(){
	std::string result = "<TaggedStatement>";

	//if(identifier != NULL){
	//	result += identifier->toStdString();
	//}

	if(statement != NULL){
		result += statement->toStdString();
	}

	result += "</TaggedStatement>";
	return result;
}

void TaggedStatement::toPrettyCode(CodeString* context){
	CodeLine* line = new CodeLine();

	line->add(identifier + ":");

	context->add(line);

	if(statement != NULL){
		statement->toPrettyCode(context);
	}
}


std::string CompoundStatement::toStdString(){
	std::string result = "<CompoundStatement>";


	if(statement_list.size() != 0){
		result += "<StatementList>";
		for( auto &i : statement_list ) {
			result += i->toStdString();
		}
		result += "</StatementList>";
	}

	result += "</CompoundStatement>";
	return result;
}

void CompoundStatement::toPrettyCode(CodeString* context){
	context->add(new CodeLine("{"));
	if( boole ) {
		CodeBlock *local_context = new CodeBlock();


		if(statement_list.size() != 0){
			for( auto &i : statement_list ) {
				i->toPrettyCode(local_context);
			}
		}

		context->add(local_context);
	}
	
	else {
		context->add(new CodeLine("\tcudaMalloc()"));
		//context.add(new CodeLine(getDimBlockGridString(CudaLoopRelation* &cuda_loop_relation)));
	}

	context->add(new CodeLine("}"));
}


std::string ExpressionStatement::toStdString(){
	std::string result = "<ExpressionStatement>";

	if(expression_list.size() != 0){
		result += "<ExpressionList>";
		for( auto &i : expression_list ) {
			result += i->toStdString();
		}
		result += "</ExpressionList>";
	}
	result += "</ExpressionStatement>";
	return result;
}

void ExpressionStatement::toPrettyCode(CodeString* context){
	CodeLine *line = new CodeLine();

	if(expression_list.size() != 0){
		for( auto &i : expression_list ) {
			i->toPrettyCode(line);
		}
	}
	if(point_virgule) {
		line->add(";");
	}
	context->add(line);
}


std::string IfSelectionStatement::toStdString() {
	std::string result = "<IfSelectionStatement token= '" + std::to_string(token) + "'>";

	result += "<ExpressionList>";
	for( auto &i : expression){
		result += i->toStdString();
	}
	result += "</ExpressionList>";

	result += statement->toStdString();

	result += "</IfSelectionStatement>";
	return result;
}

void IfSelectionStatement::toPrettyCode(CodeString* context) {
	CodeLine* line = new CodeLine();

	line->add("if (");
	for( auto &i : expression){
		i->toPrettyCode(line);
	}
	line->add(")");
	context->add(line);
	statement->toPrettyCode(context);
}


std::string IfElseSelectionStatement::toStdString() {
	std::string result = "<IfElseSelectionStatement>";

	result += "<ExpressionList>";
	for( auto &i : expression){
		result += i->toStdString();
	}
	result += "</ExpressionList>";
	result += statement->toStdString();
	result += statement_else->toStdString();
	result += "</IfElseSelectionStatement>";
	return result;
}

void IfElseSelectionStatement::toPrettyCode(CodeString* context) {
	CodeLine* line = new CodeLine("if (");

	for( auto &i : expression){
		i->toPrettyCode(line);
	}

	line->add(")");
	context->add(line);
	statement->toPrettyCode(context);
	context->add(new CodeLine("else"));
	statement_else->toPrettyCode(context);
}


std::string SwitchSelectionStatement::toStdString() {
	std::string result = "<SwitchSelectionStatement>";

	result += "<ExpressionList>";
	for( auto &i : expression){
		result += i->toStdString();
	}
	result += "</ExpressionList>";

	result += statement->toStdString();

	result += "</SwitchSelectionStatement>";
	return result;
}

void SwitchSelectionStatement::toPrettyCode(CodeString* context) {
	CodeLine *line = new CodeLine("switch (");
	for( auto &i : expression){
		i->toPrettyCode(line);
	}
	line->add(")");
	context->add(line);
	statement->toPrettyCode(context);
}


std::string WhileIterationStatement::toStdString() {
	std::string result = "<WhileIterationStatement>";

	result += "<ExpressionList>";
	for(auto &i : expression){
		result += i->toStdString();
	}
	result += "</ExpressionList>";

	result += statement->toStdString();

	result += "</WhileIterationStatement>";
	return result;
}

void WhileIterationStatement::toPrettyCode(CodeString* context) {
	CodeLine* line = new CodeLine("while (");
	for( auto &i : expression){
		i->toPrettyCode(line);
	}

	line->add(")");
	context->add(line);
	statement->toPrettyCode(context);
}


std::string DoWhileIterationStatement::toStdString() {
	std::string result = "<DoWhileIterationStatement>";
	result += statement->toStdString();
	result += "<ExpressionList>";
	for(auto &i : expression){
		result += i->toStdString();
	}
	result += "</ExpressionList>";

	result += "</DoWhileIterationStatement>";
	return result;
}

void DoWhileIterationStatement::toPrettyCode(CodeString* context) {

	context->add(new CodeLine("do"));
	statement->toPrettyCode(context);
	CodeLine* line = new CodeLine("while (");

	for( auto &i : expression){
		i->toPrettyCode(line);
	}

	line->add(");");
	context->add(line);
}

std::string ForSimpleIterationStatement::toStdString() {
	std::string result = "<ForSimpleIterationStatement>";

	result += expression_statement1->toStdString();
	result += expression_statement2->toStdString();
	result += statement->toStdString();

	result += "</ForSimpleIterationStatement>";
	return result;
}

void ForSimpleIterationStatement::toPrettyCode(CodeString* context) {
	CodeLine* line = new CodeLine("for ( ");

	expression_statement1->toPrettyCode(line);
	line->add(" ");
	expression_statement2->toPrettyCode(line);
	line->add(" )");
	context->add(line);
	statement->toPrettyCode(context);
}


std::string ForCompoundIterationStatement::toStdString() {
	std::string result = "<ForCompoundIterationStatement>";

	result += expression_statement1->toStdString();
	result += expression_statement2->toStdString();
	result += "<ExpressionList>";
		for(auto &i : expression){
			result += i->toStdString();
		}
		result += "</ExpressionList>";

	result += statement->toStdString();

	result += "</ForCompoundIterationStatement>";
	return result;
}

void ForCompoundIterationStatement::toPrettyCode(CodeString* context) {

	if (isInACudaFunction) {
		point_virgule = false;
		CodeLine* line = new CodeLine("if (");
		expression_statement2->toPrettyCode(line);
		line->add(")");
		point_virgule = true;
		context->add(line);
		statement->toPrettyCode(context);
	}
	else {
		CodeLine* line = new CodeLine("for ( ");

		expression_statement1->toPrettyCode(line);
		line->add(" ");
		expression_statement2->toPrettyCode(line);
		line->add(" ");
		for(auto &i : expression){
			i->toPrettyCode(line);
		}
		line->add(" )");
		context->add(line);
		statement->toPrettyCode(context);
	}
}

std::string JumpStatement::toStdString(){
	std::string result = "<JumpStatement>";

	if(expression_list.size() != 0){
		result += "<ExpressionList>";
		for(auto &i : expression_list){
			result += i->toStdString();
		}
		result += "</ExpressionList>";
	}

	result += "</JumpStatement>";
	return result;
}

void JumpStatement::toPrettyCode(CodeString* context){
	CodeLine *line = new CodeLine();

	if(token == GOTO){
		line->add("goto ");
		line->add(identifier);
		line->add(";");
	}

	if(token == CONTINUE){
		line->add("continue;");
	}

	if(token == BREAK){
		line->add("break;");
	}

	if(token == RETURN){
		line->add("return");
		if(expression_list.size() != 0){
			line->add(" ");
			for(auto &i : expression_list){
				i->toPrettyCode(line);
			}
		}
		line->add(";");
	}

	context->add(line);
}


std::string FunctionDefinition::toStdString(){
	std::string result = "<FunctionDefinition>";

	if(declaration_specifier_list.size() != 0){
		result += "<DeclarationSpecifierList>";
		for( auto &i : declaration_specifier_list ) {
			result += i->toStdString();
		}
		result += "</DeclarationSpecifierList>";
	}

	if(declarator != NULL){
		result += declarator->toStdString();
	}

	if(declaration_list.size() != 0){
		result += "<DeclarationList>";
		for( auto &i : declaration_list ) {
			result += i->toStdString();
		}
		result += "</DeclarationList>";
	}

	if(compound_statement != NULL){
		result += compound_statement->toStdString();
	}

	result += "</FunctionDefinition>";
	return result;
}



void FunctionDefinition::toPrettyCode(CodeString* context){
	// Normal or cuda kernel function

	CodeLine *line = new CodeLine();

	if (boole) {
			if(declaration_specifier_list.size() != 0){
			for( auto &i : declaration_specifier_list ) {
				if (isACudaFunction)
					context->add(new CodeLine("__global__"));
				i->toPrettyCode(line);
			}
		}

		if(declarator != NULL){
			if (isACudaFunction) {
				line->add(" kernel_");
				declarator->toPrettyCode(line);
			}
			else {
				line->add(" ");
				declarator->toPrettyCode(line);
			}
			
		}

		if(declaration_list.size() != 0){

			for( auto &i : declaration_list ) {
				i->toPrettyCode(line);
			}
		}

		context->add(line);

		if(compound_statement != NULL){
			compound_statement->toPrettyCode(context);
		}
	}

	else {
		if(declaration_specifier_list.size() != 0){
			for( auto &i : declaration_specifier_list ) {
				i->toPrettyCode(line);
			}
		}

		if(declarator != NULL){
				line->add(" ");
				declarator->toPrettyCode(line);
			}
			
		


		context->add(line);

		if(compound_statement != NULL){
			compound_statement->toPrettyCode(context);
		}
	}
	

	//Empty normal function for kernel calling
	// if(isACudaFunction) {
	//
	// 	CodeLine *line = new CodeLine();
	// 	if(declaration_specifier_list.size() != 0){
	// 		for( auto &i : declaration_specifier_list ) {
	// 			i->toPrettyCode(line);
	// 		}
	// 	}
	//
	// 	if(declarator != NULL){
	// 		line->add(" ");
	// 		declarator->toPrettyCode(line);
	// 	}
	//
	// 	if(declaration_list.size() != 0){
	// 		for( auto &i : declaration_list ) {
	// 			i->toPrettyCode(line);
	// 		}
	// 	}
	// 	context->add(line);
	// }


}


std::string CudaDefinition::toStdString(){

	std::string result = "<CudaDefinition>";

	if(pragma_cuda){
			result += pragma_cuda->toStdString();
	}
	result += functionDefinition->toStdString();
	result += "</CudaDefinition>";

	return result;
}


void CudaDefinition::toPrettyCode(CodeString* context){

	CodeLine *line = new CodeLine();

	pragma_cuda->toPrettyCode(context);
	functionDefinition->toPrettyCode(context);

	boole = false;

	if (functionDefinition->isACudaFunction) {
		functionDefinition->toPrettyCode(context);

	}
	
}

std::string PragmaCuda::toStdString(){

	std::string result = "<PragmaCuda>" ;
	if(cuda_param_list.size() != 0){
		result += "<CudaParamsList>";
		for( auto &i : cuda_param_list ) {
			result += i->toStdString();
		}
		result += "</CudaParamsList>\n";
	}
	result += "</PragmaCuda>";
	return result;
}

void PragmaCuda::toPrettyCode(CodeString* context){
	CodeLine *line = new CodeLine();
	if(cuda_param_list.size() != 0){
		for( auto &i : cuda_param_list ) {
			i->toPrettyCode(line);
		}
	}
	context->add(line);
}


std::string CudaParam::toStdString(){
	std::string result = "";

	result += "<CudaParam>";


	std::string var_token;

	if(token == THREAD_LOOP){
		var_token = "<ThreadLoop>thread_loop</ThreadLoop>";
	}
	else if (token == BLOCK_SIZE){
		var_token = "<BlockSize>block_size</BlockSize>";
	}
	else {
		var_token = "<GridSize>grid_size</GridSize>";
	}

	result += var_token;

	if(cuda_params_args_list.size() != 0){
		result += "<CudaParamArgsList>";
		for( auto &i : cuda_params_args_list ) {
			result += i->toStdString();
		}
		result += "</CudaParamArgsList>";
	}
	result += "</CudaParam>\n";

	return result;
}

void CudaParam::toPrettyCode(CodeString* context){
	CodeLine *line = new CodeLine();
	context->add(line);
}


std::string CudaParamArgs::toStdString(){
	std::string result = "<CudaParamArg>";

	result += *arg;

	result += "</CudaParamArg>";

	return result;
}

void CudaParamArgs::toPrettyCode(CodeString* context){
	CodeLine *line = new CodeLine();

	context->add(line);
}


std::string getDimBlockGridString(CudaLoopRelation* &cuda_loop_relation) {
	std::vector<std::string> block_size_variables;
	std::vector<std::string> grid_size_variables;

	std::string nbr_thread_op_str = "";
	std::string nbr_thread_str = "dim3(";
	std::string nbr_block_str = "dim3(";

	for (auto cudaParam : cuda_loop_relation->cuda_definition->pragma_cuda->cuda_param_list) {

		if (cudaParam->token == BLOCK_SIZE) {
			for (auto CudaParamArg : cudaParam->cuda_params_args_list) {
				block_size_variables.push_back(*(CudaParamArg->arg));
			}
		}

		if (cudaParam->token == GRID_SIZE) {
			for (auto CudaParamArg : cudaParam->cuda_params_args_list) {
				grid_size_variables.push_back(*(CudaParamArg->arg));
			}
		}
	}

	if(block_size_variables.size() != 0) {
		for(std::string block_size_variable : block_size_variables) {
			nbr_thread_op_str += block_size_variable + "*";
			nbr_thread_str += block_size_variable +", ";
		}
		nbr_thread_str.pop_back();
		nbr_thread_str.pop_back();
		nbr_thread_op_str.pop_back();

		if(grid_size_variables.size() != 0) {
			for(std::string grid_size_variable : grid_size_variables) {
				nbr_block_str += "(" + grid_size_variable + " + " + nbr_thread_op_str + " - 1 ) / " + nbr_thread_op_str + ", ";
			}
			nbr_block_str.pop_back();
			nbr_block_str.pop_back();
		  return nbr_block_str+ "), " + nbr_thread_str +")";
		} else {
			return "dim3(1, 1, 1), " + nbr_thread_str +")";
		}
	} else {
		if(grid_size_variables.size() != 0) {
			for(std::string grid_size_variable : grid_size_variables) {
				nbr_block_str += grid_size_variable + ", ";
			}
			nbr_block_str.pop_back();
			nbr_block_str.pop_back();
			return nbr_block_str + "), dim3(1, 1, 1)";
		} else {
			std::cout << "[WARNING] Neither grid size or block size defined, please modify manually these values." << std::endl;
			return "dim3(/*grid*/), dim3(/*block*/))";
		}
	}
}



void checkVariables(std::vector<std::string> variable_used_list, std::vector<IdentifierDeclarator*> variable_declared_identifier_list){

	std::vector<std::string> variable_declared_list;
	for(IdentifierDeclarator* identifier_declarator : variable_declared_identifier_list) {
		variable_declared_list.push_back(identifier_declarator->identifier);
	}
	std::set<std::string> declared(variable_declared_list.begin(), variable_declared_list.end());
	std::set<std::string> used(variable_used_list.begin(), variable_used_list.end());
	std::set<std::string> result;
	std::set_difference(used.begin(), used.end(), declared.begin(), declared.end(),
    std::inserter(result, result.end()));
	if(result.size()) {
		std::string variable_not_declared_concat;
		for(auto &i : result) {
			variable_not_declared_concat += "\"" + i +"\", ";
		}
		variable_not_declared_concat.pop_back();
		variable_not_declared_concat.pop_back();

		std::cout << "[WARNING] Variable(s) " << variable_not_declared_concat << " may not be reachable" << std::endl;
	}
}

void threadLoopIdentifierSave(CudaLoopRelation* &cuda_loop_relation){
	for(auto cudaParam : cuda_loop_relation->cuda_definition->pragma_cuda->cuda_param_list) {
		if(cudaParam->token == THREAD_LOOP) {
			cuda_loop_relation->thread_loop_identifier = *(cudaParam->cuda_params_args_list.front()->arg);
			for(IdentifierDeclarator* identifier_declarator :cuda_loop_relation->cuda_variable_declared_list) {
				if(identifier_declarator->identifier == cuda_loop_relation->thread_loop_identifier) {
					identifier_declarator->isGtid=true;
				}
			}
		}
	}
}


void integrityTest() {

	for(CudaLoopRelation* &cuda_loop_relation : cuda_loop_relation_list) {


		std::cout << getDimBlockGridString(cuda_loop_relation) << std::endl;
		threadLoopIdentifierSave(cuda_loop_relation);


		for(auto &loop : cuda_loop_relation->loop_list) {
			ForCompoundIterationStatement * for_compound = dynamic_cast<ForCompoundIterationStatement *>(loop);
			if(for_compound && for_compound->expression.size() == 1) {


				Identifier * identifier;
				std::string inc_operator;
				PostfixOperation * postfix_operation = dynamic_cast<PostfixOperation *>(for_compound->expression.back());
				UnaryOperation * unary_operation = dynamic_cast<UnaryOperation *>(for_compound->expression.back());

				if(postfix_operation) {
					identifier = dynamic_cast<Identifier *>(postfix_operation->operand);
					inc_operator = postfix_operation->unary_operator->value;
				} else if(unary_operation){
					identifier = dynamic_cast<Identifier *>(unary_operation->operand);
					inc_operator = unary_operation->unary_operator->value;
				}

				if(identifier && cuda_loop_relation->thread_loop_identifier == identifier->value) {

					checkVariables(cuda_loop_relation->cuda_variable_used_list, cuda_loop_relation->cuda_variable_declared_list);
					if(inc_operator != "++") {
						std::cout << "[WARNING] Find \"" << inc_operator << "\" instead of \"++\"" << std::endl;
					}
					for_compound->isInACudaFunction = true;
					cuda_loop_relation->cuda_definition->functionDefinition->isACudaFunction=true;
				}
			}
		}
	}
}
