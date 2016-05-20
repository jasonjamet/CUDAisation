#include "node.hpp"
#include "ansi-c.tab.hpp"

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

std::string TranslationUnit::generateCode(CodeContext *context){
	context->push_block();

	if(statements.size() != 0){
		int size = statements.size();
		for ( auto &i : statements) {
			i->generateCode(context);
		}
	}

	context->pop_block();

	return "";
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

std::string PointerDeclarator::generateCode(CodeContext* context){
	std::string result = "";

	if(pointer != NULL){
		result += pointer->generateCode(context);
	}

	if(direct_declarator != NULL){
		result += direct_declarator->generateCode(context);
	}

	return result;
}

std::string IdentifierDeclarator::toStdString(){
	std::string result = "<IdentifierDeclarator>";
	result += identifier;
	result += "</IdentifierDeclarator>";

	return result;
}

void IdentifierDeclarator::toPrettyCode(CodeString* context){
	context->add(identifier);
}

std::string IdentifierDeclarator::generateCode(CodeContext *context){

	if (context->locals().find(identifier) == context->locals().end()) {
		context->locals().emplace(identifier,new Symbol(identifier));
	}
	else {
		std::cerr << identifier << " is already declared" << std::endl;
	}

	return identifier;
}

std::string Identifier::toStdString(){
	std::string result = "<Identifier value='" + value + "'></Identifier>";
	return result;
}

void Identifier::toPrettyCode(CodeString* context){
	context->add(value);
}

std::string Identifier::generateCode(CodeContext* context){

	if (context->locals().find(value) != context->locals().end()) {
		context->locals().find(value)->second->invoque();
	} else if (context->globals().find(value) != context->globals().end()) {
		context->globals().find(value)->second->invoque();
	}
	else {
		/* is not declared */
		std::cerr << value << " is not declared" << std::endl;
	}

	return value;
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

std::string Operator::generateCode(CodeContext* context){
	return value;
}

std::string Constant::toStdString(){
	std::string result = "<Constant value='" + value + "'></Constant>";
	return result;
}

void Constant::toPrettyCode(CodeString* context){
	context->add(value);
}

std::string Constant::generateCode(CodeContext *context){
	std::string ret = context->new_temp();
	context->buffer << ret << " = " << value << "\n";
	return ret;
}

std::string StringLiteral::toStdString(){
	std::string result = "<StringLiteral value='" + value + "'></StringLiteral>";
	return result;
}

void StringLiteral::toPrettyCode(CodeString* context){
	context->add(value);
}

std::string StringLiteral::generateCode(CodeContext *context){
	std::string ret = context->new_temp();
	context->buffer << ret << " = " << value << "\n";
	return ret;
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

std::string PrimaryExpression::generateCode(CodeContext* context){
	std::string result = "";

	if(expression_list.size() != 0){
		for( auto &i : expression_list ){
			result += i->generateCode(context);
		}
	}

    return result;
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

std::string PostfixOperation::generateCode(CodeContext *context){
    std::string result = "";
	std::string tmp = "";
	std::string op = "";

    if(operand != NULL){
        tmp = operand->generateCode(context);
    }

	if(unary_operator != NULL){
		op = unary_operator->generateCode(context);
	}

	result = context->new_temp();
	context->buffer << result << " = " << op << " " << tmp << "\n";

    return result;
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

std::string ArrayAccess::generateCode(CodeContext* context){
	/* TODO test and improve this */
	std::string t1 = "";
	std::string t2 = "";
	std::string result = "";

	if(postfix_expression != NULL){
		t1 = postfix_expression->generateCode(context);
	}

	if(expression.size() != 0){
		for( auto &i : expression){
			t2 = i->generateCode(context);
		}
	}

	result = context->new_temp();
	context->buffer << result << " = " << t1 << "[" << t2 << "]\n";
	return result;
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

std::string FunctionCall::generateCode(CodeContext* context){
	std::string result = "";
	std::string tmp = "";

	std::vector<std::string> params;

	if(argument_expression_list.size() != 0){

		for( auto &i : argument_expression_list){
			params.insert(params.begin(),i->generateCode(context));
		}
	}

	if(postifx_expression != NULL){
		for( std::string a : params){
	  		context->buffer << "PushParam " << a << "\n";
		}

		tmp = postifx_expression->generateCode(context);
		result = context->new_temp();
		context->buffer << result << " = " << " LCall " << tmp << "\n";
		context->buffer << "PopParams\n";
	}

	return result;
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

std::string UnaryOperation::generateCode(CodeContext* context){
    std::string result = "";
	std::string op = "";
	std::string tmp = "";

	if(unary_operator != NULL){
		op = unary_operator->generateCode(context);
	}

    if(operand != NULL){
        tmp = operand->generateCode(context);
    }

	result = context->new_temp();
	context->buffer << result << " = " << op << " " << tmp << "\n";

    return result;
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

std::string BinaryOperation::generateCode(CodeContext* context){
	std::string tmp = "";
	std::string left = "";
	std::string right = "";
	std::string op = "";

	if(left_operand != NULL){
        left = left_operand->generateCode(context);
    }

	if(binary_operator != NULL){
		op = binary_operator->generateCode(context);
	}

    if(right_operand != NULL){
        right = right_operand->generateCode(context);
    }
	tmp = context->new_temp();
	context->buffer << tmp << " = " << left << " " << op << " " << right << "\n";

    return tmp;
}

std::string LogicalOperation::generateCode(CodeContext* context){
	std::string tmp = "";
	std::string left = "";
	std::string right = "";
	std::string op = "";

	if(left_operand != NULL){
        left = left_operand->generateCode(context);
    }

	if(binary_operator != NULL){
		op = binary_operator->generateCode(context);
	}

    if(right_operand != NULL){
        right = right_operand->generateCode(context);
    }

	tmp = context->new_temp();
	std::string L1 = context->new_label();
	std::string L2 = context->new_label();
	std::string L3 = context->new_label();

	context->buffer << "if( " << left << " " + op + " " << right << " ) goto "<< L1 << "\n";
	context->buffer << "goto " << L2 << "\n";
	context->buffer << L1 << ":\n";
	context->buffer << tmp << " = " << 1 << "\n";
	context->buffer << "goto " << L3 << "\n";
	context->buffer << L2 << ":\n";
	context->buffer << tmp << " = " << 0 << "\n";
	context->buffer << L3 << ":\n";

    return tmp;
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

std::string ConditionalExpression::generateCode(CodeContext* context){
	std::string t1 = "";
	std::string t2 = "";
	std::string t3 = "";
	std::string result = "";
	std::string LFalse = "";
	std::string LEnd = "";

	if(logical_or_expression != NULL){
        t1 = logical_or_expression->generateCode(context);
    }

	result = context->new_temp();
	LFalse = context->new_label();
	context->buffer << "if " << t1 << " == 0 goto " << LFalse << "\n";
	if(expression.size() != 0){
        for( auto &i : expression ) {
            t2 = i->generateCode(context);
        }
	}
	context->buffer << result << " = " << t2 <<  "\n";
	LEnd = context->new_label();
	context->buffer << "goto " << LEnd << "\n";
	context->buffer << LFalse << ":\n";
	if(conditional_expression != NULL){
        t3 = conditional_expression->generateCode(context);
    }
	context->buffer << result << " = " << t3 <<  "\n";
	context->buffer << "goto " << LEnd << "\n";
	context->buffer << LEnd << ":\n";
	return result;
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

std::string AssignmentExpression::generateCode(CodeContext* context){
	std::string tmp1 = "";
	std::string op = "";
	std::string tmp2 = "";

	if(unary_expression != NULL){
		tmp1 = unary_expression->generateCode(context);
	}

	if(assignment_operator != NULL){
		op = assignment_operator->generateCode(context);
	}

	if(assignment_expression != NULL){
		tmp2 = assignment_expression->generateCode(context);
	}

	context->buffer << tmp1 << " " << op << " " << tmp2 << "\n";

	return tmp1;
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

std::string ArrayDeclarator::generateCode(CodeContext* context){
	std::string result = "";

	if(direct_declarator != NULL){
		result = direct_declarator->generateCode(context);
	}

	if(constant_expression != NULL){
		//constant_expression->generateCode(context);
	}

	return result;
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

std::string FunctionDeclarator::generateCode(CodeContext* context){
	std::string result = "";

	if(direct_declarator != NULL){
		result = direct_declarator->generateCode(context);
	}

	context->push_block();

	if(parameter_type_list.size() != 0){
		parameter_type_list.size();
		for ( auto &i : parameter_type_list) {
			i->generateCode(context);
		}
	}

	return result;
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

std::string NestedDeclarator::generateCode(CodeContext* context){
	std::string result = "";

	if(declarator != NULL){
		result = declarator->generateCode(context);
	}

	return result;
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

std::string Pointer::generateCode(CodeContext* context){
	std::string result = "*";

	if(child){
		result += child->generateCode(context);
	}

	/** Get specifiers childs std strings */
	//if(type_qualifier_list.size() != 0){
	//	for ( auto &i : type_qualifier_list) {
	//		i->toPrettyCode(context);
	//	}
	//}
	return result;
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

std::string InitDeclarator::generateCode(CodeContext* context){
	std::string tmp1 = "";
	std::string tmp2 = "";

	if(declarator != NULL){
		tmp1 = declarator->generateCode(context);
	}

	if(initializer != NULL){
		tmp2 = initializer->generateCode(context);
		context->buffer << tmp1 << " = " << tmp2 << "\n";
	}

	return tmp1;
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

std::string Initializer::generateCode(CodeContext *context){
	std::string tmp = "";

    if(assignment_expression != NULL){
        tmp = assignment_expression->generateCode(context);
    }

	return tmp;
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

std::string Declaration::generateCode(CodeContext *context){
	/** Get specifiers childs std strings */
	if(declaration_specifiers.size() != 0 ){
		for ( auto &i : declaration_specifiers ) {
			i->generateCode(context);
		}
	}

	/** Get specifiers childs std stringqs */
	if(init_declarator_list.size() != 0){
		for( auto &i : init_declarator_list ) {
			i->generateCode(context);
		}
	}

	return "";
}

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

std::string ParameterDeclaration::generateCode(CodeContext* context){
	std::string result = "";

	if(declarator != NULL){
		result = declarator->generateCode(context);
	}

	return result;
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

std::string CaseStatement::generateCode(CodeContext* context){
	std::string result = "";
	/* TODO: implement this */
	return result;
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

std::string DefaultStatement::generateCode(CodeContext* context){
	return ""; /* TODO: implement this */
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

std::string TaggedStatement::generateCode(CodeContext* context){

	context->buffer << identifier;
	context->buffer << ":\n";

	if(statement != NULL){
		statement->generateCode(context);
	}

	return "";
}

std::string CompoundStatement::toStdString(){
	std::string result = "<CompoundStatement>";

    if(declaration_list.size() != 0){
		result += "<DeclarationList>";
		for( auto &i : declaration_list ) {
			result += i->toStdString();
		}
		result += "</DeclarationList>";
	}

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
	CodeBlock *local_context = new CodeBlock();

    if(declaration_list.size() != 0){
		for( auto &i : declaration_list ) {
			i->toPrettyCode(local_context);
		}
	}

	if(statement_list.size() != 0){
		for( auto &i : statement_list ) {
			i->toPrettyCode(local_context);
		}
	}

	context->add(local_context);
	context->add(new CodeLine("}"));
}

std::string CompoundStatement::generateCode(CodeContext* context){
	std::string result = "";

    if(declaration_list.size() != 0){
		for( auto &i : declaration_list ) {
			i->generateCode(context);
		}
	}

	if(statement_list.size() != 0){
		for( auto &i : statement_list ) {
			i->generateCode(context);
		}
	}

	return result;
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

	line->add(";");
	context->add(line);
}

std::string ExpressionStatement::generateCode(CodeContext* context){
	std::string result = "";

	if(expression_list.size() != 0){
		for( auto &i : expression_list ) {
			result = i->generateCode(context);
		}
	}

	return result;
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

std::string IfSelectionStatement::generateCode(CodeContext* context) {
	std::string t1 = "";
	std::string LEnd = "";

	for( auto &i : expression){
		t1 = i->generateCode(context);
	}

	LEnd = context->new_label();
	context->buffer << "if " << t1 << " == 0 goto " << LEnd << "\n";
	statement->generateCode(context);
	context->buffer << LEnd << ":\n";
	return "";
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

std::string IfElseSelectionStatement::generateCode(CodeContext* context) {
	std::string t1 = "";
	std::string LFalse = "";
	std::string LEnd = "";

	for( auto &i : expression){
		t1 = i->generateCode(context);
	}

	LFalse = context->new_label();
	LEnd = context->new_label();
	context->buffer << "if " << t1 << " == 0 goto " << LFalse << "\n";
	statement->generateCode(context);
	context->buffer << "goto " << LEnd << "\n";
	context->buffer << LFalse << ":\n";
	statement_else->generateCode(context);
	context->buffer << LEnd << ":\n";
	return "";
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

std::string SwitchSelectionStatement::generateCode(CodeContext* context) {
	/* TODO implement this*/
	return "";
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

std::string WhileIterationStatement::generateCode(CodeContext *context){
	std::string t1 = "";
	std::string LBegin = "";
	std::string LEnd = "";

	LBegin = context->new_label();
	LEnd = context->new_label();

	context->buffer << LBegin << ":\n";
	for( auto &i : expression){
		t1 = i->generateCode(context);
	}

	context->buffer << "if " << t1 << " == 0 goto " << LEnd << "\n";
	statement->generateCode(context);
	context->buffer << "goto " << LBegin << "\n";
	context->buffer << LEnd << ":\n";
	return "";
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

std::string DoWhileIterationStatement::generateCode(CodeContext* context){
	std::string t1 = "";
	std::string LBegin = "";

	LBegin = context->new_label();

	context->buffer << LBegin << ":\n";
	statement->generateCode(context);

	for( auto &i : expression){
		t1 = i->generateCode(context);
	}

	context->buffer << "if " << t1 << " == 1 goto " << LBegin << "\n";
	return "";
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

std::string ForSimpleIterationStatement::generateCode(CodeContext* context) {
	std::string L1 = "";
	std::string L2 = "";
	std::string L3 = "";
	std::string L4 = "";
	std::string t1 = "";

	expression_statement1->generateCode(context);

	L1 = context->new_label();
	L2 = context->new_label();
	L3 = context->new_label();
	L4 = context->new_label();

	context->buffer << L1 << ":\n";
	t1 = expression_statement2->generateCode(context);
	context->buffer << "if " << t1 << " == 1 goto " << L2 << "\n";
	context->buffer << "goto " << L3 << "\n";
	context->buffer << L4 << ":\n";
	context->buffer << "goto " << L1 << "\n";
	context->buffer << L2 << ":\n";
	statement->generateCode(context);
	context->buffer << "goto " << L4 << "\n";
	context->buffer << L3 << ":\n";
	return "";
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

std::string ForCompoundIterationStatement::generateCode(CodeContext* context) {
	std::string L1 = "";
	std::string L2 = "";
	std::string L3 = "";
	std::string L4 = "";
	std::string t1 = "";

	expression_statement1->generateCode(context);

	L1 = context->new_label();
	L2 = context->new_label();
	L3 = context->new_label();
	L4 = context->new_label();

	context->buffer << L1 << ":\n";
	t1 = expression_statement2->generateCode(context);
	context->buffer << "if " << t1 << " == 1 goto " << L2 << "\n";
	context->buffer << "goto " << L3 << "\n";
	context->buffer << L4 << ":\n";
	for(auto &i : expression){
		i->generateCode(context);
	}
	context->buffer << "goto " << L1 << "\n";
	context->buffer << L2 << ":\n";
	statement->generateCode(context);
	context->buffer << "goto " << L4 << "\n";
	context->buffer << L3 << ":\n";
	return "";
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

std::string JumpStatement::generateCode(CodeContext* context){

	if(token == GOTO){
		context->buffer << "goto " << identifier << "\n" ;
	}

	if(token == CONTINUE){
		/* TODO implement this */
	}

	if(token == BREAK){
		/* TODO implement this */
	}

	if(token == RETURN && expression_list.size() == 0){
		context->buffer << "return\n";
	}

	if(token == RETURN && expression_list.size() != 0){
		std::string tmp = "";
		if(expression_list.size() != 0){
			for(auto &i : expression_list){
				tmp = i->generateCode(context);
			}
		}

		context->buffer << "return " << tmp << "\n";
	}

	return "";
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
	CodeLine *line = new CodeLine();

	if(declaration_specifier_list.size() != 0){
		for( auto &i : declaration_specifier_list ) {
			i->toPrettyCode(line);
		}
	}

	if(declarator != NULL){
		line->add(" ");
		declarator->toPrettyCode(line);
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

std::string FunctionDefinition::generateCode(CodeContext* context){
	std::string result = "";

	if(declarator != NULL){
		result += declarator->generateCode(context);
	}

	context->buffer << result << ":" << "\n" << "BeginFunc\n";

	if(declaration_list.size() != 0){
		for( auto &i : declaration_list ) {
			i->generateCode(context);
		}
	}

	if(compound_statement != NULL){
		compound_statement->generateCode(context);
	}

	context->buffer << "EndFunc\n\n";

	context->pop_block();

	return result;
}


//////////////////////////////////////


std::string PragmaCuda::toStdString(){
	std::string result = "<PragmaCuda>" + token1 + " " + token2;

	if(cuda_params.size() != 0){
		result += "<CudaParamsList>";
		for( auto &i : cuda_params ) {
			result += i->toStdString();
		}
		result += "</CudaParamsList>";
	}

	if(iteration_statement.size() != 0){
		result += "<IterationStatement>";
		for( auto &i : iteration_statement ) {
			result += i->toStdString();
		}
		result += "</IterationStatement>";
	}

	result += "</PragmaCuda>";
	return result;
}

void PragmaCuda::toPrettyCode(CodeString* context){
	CodeLine *line = new CodeLine();

	if(cuda_params.size() != 0){
		for( auto &i : cuda_params ) {
			i->toPrettyCode(line);
		}
	}

	if(iteration_statement.size() != 0){
		for( auto &i : iteration_statement ) {
			i->toPrettyCode(line);
		}
	}

	context->add(line);

}

std::string PragmaCuda::generateCode(CodeContext* context){
	std::string result = "";

	if(declarator != NULL){
		result += declarator->generateCode(context);
	}

	context->buffer << result << ":" << "\n" << "BeginFunc\n";

	if(declaration_list.size() != 0){
		for( auto &i : declaration_list ) {
			i->generateCode(context);
		}
	}

	if(compound_statement != NULL){
		compound_statement->generateCode(context);
	}
	
	context->buffer << "EndFunc\n\n";

	context->pop_block();

	return result;
}
