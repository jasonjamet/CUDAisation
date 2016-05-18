typedef struct t_token {
  std::string value;
} t_token;

typedef struct t_primary_expression {
  t_token identifier;
  t_constant constant;
  t_string string;
  t_expression expression;
  t_generic_expression;
}

typedef struct t_constant {
  t_token i_constant;
  t_token f_constant;
  t_token enumeration_constant;
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
