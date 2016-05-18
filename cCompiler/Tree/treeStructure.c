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