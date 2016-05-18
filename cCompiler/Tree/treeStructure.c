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

typedef struct t_enumeration_constant {
  t_token IDENTIFIER;
} t_enumeration_constant;

typedef struct t_string {
  t_token STRING_LITERLA;
  t_token FUNC_NAME;
} t_string;

typedef struct t_generic_selection {
  t_token GENERIC;
  t_assignment_expression;
  t_generic_assoc_list;
} t_generic_selection;

typedef struct t_generic_assoc_list {
  t_generic_association generic_association;
  t_generic_assoc_list gneric_assoc_list;
} t_generic_assoc_list

typedef struct t_postfix_expression {
  t_primary_expression primary_expression;
  t_postfix_expression postfix_expression;
  t_argument_expression_list argument_expression_list;
  t_token IDENTIFIER;
  t_token PTR_OP;
  t_token INC_OP;
  t_token DEC_OP;
  t_type_name type_name;
  t_initializer_list;
} t_postfix_expression;

typedef struct t_argument_expression_list {
  t_assignment_expression assignment_expression;
  t_argument_expression_list argument_expression_list;
} t_argument_expression_list;

typedef struct t_unary_expression {
  t_postfix_expression postfix_expression;
  t_token INC_OP;
  t_token DEC_OP;
  t_unary_expression unary_expression;
  t_unary_operator unary_operator;
  t_cast_expression cast_expression;
  t_token SIZEOF;
  t_token ALIGNOF;
  t_type_name type_name;
} t_unary_expression;

typedef struct t_unary_operator {
  char operator;
} t_unary_operator;

typedef struct t_cast_expression {
  t_unary_expression unary_expression;
  t_type_name type_name;
  t_cast_expression cast_expression;
} t_cast_expression;

typedef struct t_multiplicative_expression {
  t_cast_expression cast_expression;
  t_multiplicative_expression multiplicative_expression;
  t_cast_expression cast_expression;
} t_multiplicative_expression;

typedef struct t_additive_expression {
  t_multiplicative_expression multiplicative_expression;
  t_additive_expression additive_expression;
} t_additive_expression;

typedef struct t_shift_expression {
  t_additive_expression additive_expression;
  t_shift_expression shift_expression;
  t_token LEFT_OP;
  t_token RIGHT_OP;
} t_shift_expression;

typedef struct t_relational_expression {
  t_shift_expression shift_expression;
  t_relational_expression relational_expression;
  t_token LE_OP;
  t_token GE_OP;
}

typedef struct t_equality_expression {
  t_relational_expression relational_expression;
  t_equality_expression equality_expression;
  t_relational_expression relational_expression;
  t_token EQ_OP;
  t_token NE_OP;
} t_equality_expression;

typedef struct t_and_expression {
  t_equality_expression equality_expression;
  t_and_expression and_expression;
} t_and_expression;

typedef struct t_exclusive_or_expression {
  t_and_expression and_expression;
  t_exclusive_or_expression exclusive_or_expression;
} t_exclusive_or_expression;

typedef struct t_inclusive_or_expression {
  t_exclusive_or_expression exclusive_or_expression;
  t_inclusive_or_expression inclusive_or_expression;
} t_inclusive_or_expression;

typedef struct t_logical_and_expression {
  t_inclusive_or_expression inclusive_or_expression;
  t_logical_and_expression logical_and_expression;
  t_token AND_OP;
} t_logical_and_expression;

typedef struct t_logical_or_expression {
  t_logical_and_expression logical_and_expression;
  t_logical_or_expression logical_or_expression;
  t_token OR_OP;
} t_logical_or_expression;

typedef struct t_conditional_expression {
  t_logical_or_expression logical_or_expression;
  t_expression expression;
  t_conditional_expression conditional_expression;
} t_conditional_expression;

typedef struct t_assignment_expression {
  t_conditional_expression conditional_expression;
  t_unary_expression unary_expression;
  t_assignment_operator assignment_operator;
  t_assignment_expression assignment_expression;
} t_assignment_expression;

typedef struct t_assignment_operator {
  string equal;
  t_token MUL_ASSIGN;
	t_token DIV_ASSIGN;
	t_token MOD_ASSIGN;
	t_token ADD_ASSIGN;
	t_token SUB_ASSIGN;
	t_token LEFT_ASSIGN;
	t_token RIGHT_ASSIGN;
	t_token AND_ASSIGN;
	t_token XOR_ASSIGN;
	t_token OR_ASSIGN;
} t_assignment_operator;

typedef struct t_expression {
  t_assignment_expression assignment_expression;
  t_expression expression;
} t_expression;

typedef struct t_constant_expression {
  t_conditional_expression conditional_expression;
} t_constant_expression;

typedef struct t_declaration {
  t_declaration_specifiers declaration_specifiers;
  t_init_declarator_list init_declarator_list;
  t_static_assert_declaration static_assert_declaration;
} t_declaration;

typedef struct t_declaration_specifiers {
  t_storage_class_specifier storage_class_specifier;
  t_declaration_specifiers declaration_specifiers;
  t_type_specifier type_specifier;
  t_type_qualifier type_qualifier;
  t_function_specifier function_specifier;
  t_alignment_specifier alignment_specifier;
} t_declaration_specifiers;

typedef struct t_init_declarator_list {
  t_init_declarator init_declarator;
  t_init_declarator_list init_declarator_list;
} t_init_declarator_list;

typedef struct t_init_declarator {
  t_declarator declarator;
  t_initializer initializer;
} t_init_declarator;

typedef struct t_storage_class_specifier {
  t_token TYPEDEF;
  t_token EXTERN;
	t_token STATIC;
	t_token THREAD_LOCAL;
	t_token AUTO;
	t_token REGISTER;
} t_storage_class_specifier;

typedef struct t_direct_declarator {
  t_token IDENTIFIER;
  t_declarator declarator;
  t_direct_declarator direct_declarator;
  t_token STATIC;
  t_type_qualifier_list type_qualifier_list;
  t_assignment_expression assignment_expression;
  t_parameter_type_list parameter_type_list;
  t_identifier_list identifier_list;
}
