typedef struct t_token {
  std::string value;
} t_token;

typedef struct t_primary_expression {
  t_token IDENTIFIER;
  t_constant constant;
  t_string string;
  t_expression expression;
  t_generic_expression;
} t_primary_expression;

typedef struct t_constant {
  t_token I_CONSTANT;
  t_token F_CONSTANT;
  t_token ENUMERATION_CONSTANT;
} t_constant;


//240
typedef struct t_type_specifier {
  t_token VOID;
  t_token CHAR;
  t_token SHORT;
  t_token INT;
  t_token LONG;
  t_token FLOAT;
  t_token DOUBLE;
  t_token SIGNED;
  t_token UNSIGNED;
  t_token BOOL;
  t_token COMPLEX;
  t_token IMAGINARY;
  t_atomic_type_specifier atomic_type_specifier;
  t_struct_or_union_specifier struct_or_union_specifier;
  t_enum_specifier enum_specifier;
  t_token TYPEDEF_NAME;
} t_type_specifier;

typedef struct t_struct_or_union_specifier {
  t_struct_or_union struct_or_union;
  t_struct_declaration_list struct_declaration_list;
  t_token IDENTIFIER;
}

typedef struct t_struct_or_union {
  t_token STRUCT;
  t_token UNION;
} t_struct_or_union;

typedef struct t_struct_declaration_list {
  t_struct_declaration struct_declaration;
  t_struct_declaration_list struct_declaration_list;
} t_struct_declaration_list;

typedef struct t_struct_declaration {
  t_specifier_qualifier_list specifier_qualifier_list;
  t_struct_declarator_list struct_declarator_list;
  t_static_assert_declaration static_assert_declaration;
} t_struct_declaration;

typedef struct t_specifier_qualifier_list {
  t_type_specifier type_specifier;
  t_specifier_qualifier_list specifier_qualifier_list;
  t_type_qualifier type_qualifier;
} t_specifier_qualifier_list;

typedef struct t_struct_declarator_list {
  t_struct_declarator struct_declarator;
  t_struct_declarator_list struct_declarator_list;
} t_struct_declarator_list;

typedef struct t_struct_declarator {
    t_constant_expression constant_expression;
    t_declarator declarator;
} t_struct_declarator;

typedef struct t_enum_specifier {
  t_token ENUM;
  t_token IDENTIFIER;
  t_enumerator_list enumerator_list;
} t_enum_specifier;

typedef struct t_enumerator_list {
  t_enumerator enumerator;
  t_enumerator_list enumerator_list;
} t_enumerator_list;

typedef struct t_enumerator {
  t_enumeration_constant enumeration_constant;
  t_constant_expression constant_expression;
} t_enumerator;

typedef struct t_atomic_type_specifier {
  t_token ATOMIC;
  t_type_name type_name;
} t_atomic_type_specifier;

typedef struct t_type_qualifier {
  t_token CONST;
  t_token RESTRICT;
  t_token VOLATILE
  t_token ATOMIC
} t_type_qualifier;

typedef struct t_function_specifier {
  t_token INLINE;
  t_token NORETURN;
} t_function_specifier;

typedef struct t_alignment_specifier {
  t_token ALIGNAS;
  t_type_name type_name;
  t_constant_expression constant_expression;
} t_alignment_specifier;

typedef struct t_declarator {
  t_pointer pointer;
  t_direct_declarator direct_declarator;
} t_declarator;

//341


typedef struct t_pointer {
	t_type_qualifier_list type_qualifier_list;
	t_pointer pointer;
} t_pointer;

typedef struct t_type_qualifier_list {
	t_type_qualifier type_qualifier;
	t_type_qualifier_list type_qualifier_list;
} t_type_qualifier_list;

typedef struct t_parameter_type_list {
	t_parameter_list parameter_list;
	t_token ELLIPSIS;
} t_parameter_type_list;

typedef struct t_parameter_list {
	t_parameter_declaration parameter_declaration;
	t_parameter_list parameter_list;
} t_parameter_list;

typedef struct t_parameter_declaration {
	t_declaration_specifiers declaration_specifiers;
	t_declarator declarator;
	t_abstract_declarator abstract_declarator;
} t_parameter_declaration;

typedef struct t_identifier_list{
	t_token IDENTIFIER;
	t_identifier_list identifier_list;
} t_identifier_list;

typedef struct t_type_name{
	t_specifier_qualifier_list specifier_qualifier_list;
	t_abstract_declarator abstract_declarator;
} t_type_name;

typedef struct t_abstract_declarator {
	t_pointer pointer;
	t_direct_abstract_declarator direct_abstract_declarator;
} t_abstract_declarator;

typedef struct t_direct_abstract_declarator {
	t_abstract_declarator abstract_declarator;
	t_token STATIC;
	t_type_qualifier_list type_qualifier_list;
	t_assignment_expression assignment_expression;
	t_direct_abstract_declarator direct_abstract_declarator;
	t_parameter_type_list parameter_type_list;
} t_direct_abstract_declarator;

typedef struct t_initializer {
	t_initializer_list initializer_list;
	t_assignment_expression assignment_expression;
} t_initializer;

typedef struct t_initializer_list {
	t_designation designation;
	t_initializer initializer;
	t_initializer_list initializer_list;
} t_initializer_list;

typedef struct t_designation {
	t_designator_list designator_list;
} t_designation;

typedef struct t_designator_list{
	t_designator designator;
	t_designator_list designator_list;
}t_designator_list;


typedef struct t_designator {
	t_constant_expression constant_expression;
	t_token IDENTIFIER;
} t_designator;

typedef struct t_static_assert_declaration {
	t_token STATIC_ASSERT;
	t_constant_expression constant_expression;
	t_token STRING_LITERAL;
} t_static_assert_declaration;

typedef struct t_statement {
	t_labeled_statement labeled_statement;
	t_compound_statement compound_statement;
	t_expression_statement expression_statement;
	t_selection_statement selection_statement;
	t_iteration_statement iteration_statement;
	t_jump_statement jump_statement;
} t_statement;

typedef struct t_labeled_statement {
	t_token IDENTIFIER;
	t_statement statement;
	t_token CASE;
	t_constant_expression constant_expression;
	t_token DEFAULT;
} t_labeled_statement;

typedef struct t_compound_statement {
	t_block_item_list block_item_list;
} t_compound_statement;

typedef struct t_block_item_list {
	t_block_item block_item;
	t_block_item_list block_item_list;
} t_block_item_list;

typedef struct t_block_item {
	t_declaration declaration;
	t_statement statement;
} t_block_item;

typedef struct t_expression_statement {
	t_expression expression;
} t_expression_statement;

//TODO
typedef struct t_selection_statement{
	t_token IF;
	t_expression expression;
	t_statement statement;
	t_token ELSE;
	t_token SWITCH;
} t_selection_statement;



//501
typedef struct t_iteration_statement {
  t_whileLoop whileLoop;
  t_doWhileLoop doWhileLoop
  t_forLoop forLoop;
} t_iteration_statement;

typedef struct t_doWhileLoop {
  t_statement statement;
  t_whileLoop whileLoop;
  t_expression expression;
} t_doWhileLoop;

typedef struct t_whileLoop {
  t_expression expression;
  t_statement statement;
} t_whileLoop;

typedef struct t_forLoop {
  t_token FOR;
  t_declaration declaration;
  t_expression_statement expression_statementFirst;
  t_expression_statement expression_statementSecond;
  t_expression expression;
  t_statement statement;
} t_forLoop;

typedef struct t_jump_statement {
  t_token GOTO;
  t_token CONTINUE;
  t_token BREAK;
  t_token RETURN;
  t_expression expression;
} t_jump_statement;

typedef struct t_translation_unit {
  t_external_declaration external_declaration;
  t_translation_unit translation_unit;
} t_translation_unit;

typedef struct t_external_declaration {
  t_function_definition function_definition;
  t_declaration declaration;
} t_external_declaration;

typedef struct t_function_definition{
  t_declaration_specifiers declaration_specifiers;
  t_declarator declarator;
  t_declaration_list declaration_list;
  t_compound_statement compound_statement;
} t_function_definition;

typedef struct t_declaration_list {
  t_declaration declaration;
  t_declaration_list declaration_list;
} t_declaration_list;
//536 (fin)
