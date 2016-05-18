#include <string>
#include <iostream>
using namespace std;

struct t_token;
struct t_primary_expression;
struct t_constant;
struct t_enumeration_constant;
struct t_string;
struct t_generic_selection;
struct t_generic_assoc_list;
struct t_generic_association;
struct t_postfix_expression;
struct t_argument_expression_list;
struct t_unary_expression;
struct t_unary_operator;
struct t_cast_expression;
struct t_multiplicative_expression;
struct t_additive_expression;
struct t_shift_expression;
struct t_relational_expression;
struct t_equality_expression;
struct t_and_expression;
struct t_exclusive_or_expression;
struct t_inclusive_or_expression;
struct t_logical_and_expression;
struct t_logical_or_expression;
struct t_conditional_expression;
struct t_assignment_expression;
struct t_assignment_operator;
struct t_expression;
struct t_constant_expression;
struct t_declaration;
struct t_declaration_specifiers;
struct t_init_declarator_list;
struct t_init_declarator;
struct t_storage_class_specifier;
struct t_direct_declarator;
struct t_type_specifier;
struct t_struct_or_union_specifier;
struct t_struct_or_union;
struct t_struct_declaration_list;
struct t_struct_declaration;
struct t_specifier_qualifier_list;
struct t_struct_declarator_list;
struct t_struct_declarator;
struct t_enum_specifier;
struct t_enumerator_list;
struct t_enumerator;
struct t_atomic_type_specifier;
struct t_type_qualifier;
struct t_function_specifier;
struct t_alignment_specifier;
struct t_declarator;
struct t_pointer;
struct t_type_qualifier_list;
struct t_parameter_type_list;
struct t_parameter_list;
struct t_parameter_declaration;
struct t_identifier_list;
struct t_type_name;
struct t_abstract_declarator;
struct t_direct_abstract_declarator;
struct t_initializer;
struct t_initializer_list;
struct t_designation;
struct t_designator_list;
struct t_designator;
struct t_static_assert_declaration;
struct t_statement;
struct t_labeled_statement;
struct t_compound_statement;
struct t_block_item_list;
struct t_block_item;
struct t_expression_statement;
struct t_selection_statement;
struct t_iteration_statement;
struct t_doWhileLoop;
struct t_whileLoop;
struct t_forLoop;
struct t_jump_statement;
struct t_translation_unit;
struct t_external_declaration;
struct t_function_definition;
struct t_declaration_list;



typedef struct t_token {
  std::string value;
} t_token;

typedef struct t_primary_expression {
  t_token *IDENTIFIER;
  t_constant *constant;
  t_string *string;
  t_expression *expression;
  t_generic_selection *generic_selection;
} t_primary_expression;

typedef struct t_constant {
  t_token *I_CONSTANT;
  t_token *F_CONSTANT;
  t_token *ENUMERATION_CONSTANT;
} t_constant;

typedef struct t_enumeration_constant {
  t_token *IDENTIFIER;
} t_enumeration_constant;

typedef struct t_string {
  t_token *STRING_LITERLA;
  t_token *FUNC_NAME;
} t_string;

typedef struct t_generic_selection {
  t_token *GENERIC;
  t_assignment_expression *assignment_expression;
  t_generic_assoc_list *generic_assoc_list;
} t_generic_selection;

typedef struct t_generic_assoc_list {
  t_generic_association *generic_association;
  t_generic_assoc_list *gneric_assoc_list;
} t_generic_assoc_list;

typedef struct t_generic_association {
  t_type_name *type_name;
  t_assignment_expression *assignment_expression;
  t_token *DEFAULT;
} t_generic_association;

typedef struct t_postfix_expression {
  t_primary_expression *primary_expression;
  t_postfix_expression *postfix_expression;
  t_argument_expression_list *argument_expression_list;
  t_token *IDENTIFIER;
  t_token *PTR_OP;
  t_token *INC_OP;
  t_token *DEC_OP;
  t_type_name *type_name;
  t_initializer_list *initializer_list;
} t_postfix_expression;

typedef struct t_argument_expression_list {
  t_assignment_expression *assignment_expression;
  t_argument_expression_list *argument_expression_list;
} t_argument_expression_list;

typedef struct t_unary_expression {
  t_postfix_expression *postfix_expression;
  t_token *INC_OP;
  t_token *DEC_OP;
  t_unary_expression *unary_expression;
  t_unary_operator *unary_operator;
  t_cast_expression *cast_expression;
  t_token *SIZEOF;
  t_token *ALIGNOF;
  t_type_name *type_name;
} t_unary_expression;

typedef struct t_unary_operator {
  char OPERATOR;
} t_unary_operator;

typedef struct t_cast_expression {
  t_unary_expression *unary_expression;
  t_type_name *type_name;
  t_cast_expression *cast_expression;
} t_cast_expression;

typedef struct t_multiplicative_expression {
  t_cast_expression *cast_expression;
  t_multiplicative_expression *multiplicative_expression;
} t_multiplicative_expression;

typedef struct t_additive_expression {
  t_multiplicative_expression *multiplicative_expression;
  t_additive_expression *additive_expression;
} t_additive_expression;

typedef struct t_shift_expression {
  t_additive_expression *additive_expression;
  t_shift_expression *shift_expression;
  t_token *LEFT_OP;
  t_token *RIGHT_OP;
} t_shift_expression;

typedef struct t_relational_expression {
  t_shift_expression *shift_expression;
  t_relational_expression *relational_expression;
  t_token *LE_OP;
  t_token *GE_OP;
} t_relational_expression;

typedef struct t_equality_expression {
  t_relational_expression *relational_expression;
  t_equality_expression *equality_expression;
  t_token *EQ_OP;
  t_token *NE_OP;
} t_equality_expression;

typedef struct t_and_expression {
  t_equality_expression *equality_expression;
  t_and_expression *and_expression;
} t_and_expression;

typedef struct t_exclusive_or_expression {
  t_and_expression *and_expression;
  t_exclusive_or_expression *exclusive_or_expression;
} t_exclusive_or_expression;

typedef struct t_inclusive_or_expression {
  t_exclusive_or_expression *exclusive_or_expression;
  t_inclusive_or_expression *inclusive_or_expression;
} t_inclusive_or_expression;

typedef struct t_logical_and_expression {
  t_inclusive_or_expression *inclusive_or_expression;
  t_logical_and_expression *logical_and_expression;
  t_token *AND_OP;
} t_logical_and_expression;

typedef struct t_logical_or_expression {
  t_logical_and_expression *logical_and_expression;
  t_logical_or_expression *logical_or_expression;
  t_token *OR_OP;
} t_logical_or_expression;

typedef struct t_conditional_expression {
  t_logical_or_expression *logical_or_expression;
  t_expression *expression;
  t_conditional_expression *conditional_expression;
} t_conditional_expression;

typedef struct t_assignment_expression {
  t_conditional_expression *conditional_expression;
  t_unary_expression *unary_expression;
  t_assignment_operator *assignment_operator;
  t_assignment_expression *assignment_expression;
} t_assignment_expression;

typedef struct t_assignment_operator {
  string equal;
  t_token *MUL_ASSIGN;
	t_token *DIV_ASSIGN;
	t_token *MOD_ASSIGN;
	t_token *ADD_ASSIGN;
	t_token *SUB_ASSIGN;
	t_token *LEFT_ASSIGN;
	t_token *RIGHT_ASSIGN;
	t_token *AND_ASSIGN;
	t_token *XOR_ASSIGN;
	t_token *OR_ASSIGN;
} t_assignment_operator;

typedef struct t_expression {
  t_assignment_expression *assignment_expression;
  t_expression *expression;
} t_expression;

typedef struct t_constant_expression {
  t_conditional_expression *conditional_expression;
} t_constant_expression;

typedef struct t_declaration {
  t_declaration_specifiers *declaration_specifiers;
  t_init_declarator_list *init_declarator_list;
  t_static_assert_declaration *static_assert_declaration;
} t_declaration;

typedef struct t_declaration_specifiers {
  t_storage_class_specifier *storage_class_specifier;
  t_declaration_specifiers *declaration_specifiers;
  t_type_specifier *type_specifier;
  t_type_qualifier *type_qualifier;
  t_function_specifier *function_specifier;
  t_alignment_specifier *alignment_specifier;
} t_declaration_specifiers;

typedef struct t_init_declarator_list {
  t_init_declarator *init_declarator;
  t_init_declarator_list *init_declarator_list;
} t_init_declarator_list;

typedef struct t_init_declarator {
  t_declarator *declarator;
  t_initializer *initializer;
} t_init_declarator;

typedef struct t_storage_class_specifier {
  t_token *TYPEDEF;
  t_token *EXTERN;
	t_token *STATIC;
	t_token *THREAD_LOCAL;
	t_token *AUTO;
	t_token *REGISTER;
} t_storage_class_specifier;

typedef struct t_direct_declarator {
  t_token *IDENTIFIER;
  t_declarator *declarator;
  t_direct_declarator *direct_declarator;
  t_token *STATIC;
  t_type_qualifier_list *type_qualifier_list;
  t_assignment_expression *assignment_expression;
  t_parameter_type_list *parameter_type_list;
  t_identifier_list *identifier_list;
} t_direct_declarator;

typedef struct t_type_specifier {
  t_token *VOID;
  t_token *CHAR;
  t_token *SHORT;
  t_token *INT;
  t_token *LONG;
  t_token *FLOAT;
  t_token *DOUBLE;
  t_token *SIGNED;
  t_token *UNSIGNED;
  t_token *BOOL;
  t_token *COMPLEX;
  t_token *IMAGINARY;
  t_atomic_type_specifier *atomic_type_specifier;
  t_struct_or_union_specifier *struct_or_union_specifier;
  t_enum_specifier *enum_specifier;
  t_token *TYPEDEF_NAME;
} t_type_specifier;

typedef struct t_struct_or_union_specifier {
  t_struct_or_union *struct_or_union;
  t_struct_declaration_list *struct_declaration_list;
  t_token *IDENTIFIER;
} t_struct_or_union_specifier;

typedef struct t_struct_or_union {
  t_token *STRUCT;
  t_token *UNION;
} t_struct_or_union;

typedef struct t_struct_declaration_list {
  t_struct_declaration *struct_declaration;
  t_struct_declaration_list *struct_declaration_list;
} t_struct_declaration_list;

typedef struct t_struct_declaration {
  t_specifier_qualifier_list *specifier_qualifier_list;
  t_struct_declarator_list *struct_declarator_list;
  t_static_assert_declaration *static_assert_declaration;
} t_struct_declaration;

typedef struct t_specifier_qualifier_list {
  t_type_specifier *type_specifier;
  t_specifier_qualifier_list *specifier_qualifier_list;
  t_type_qualifier *type_qualifier;
} t_specifier_qualifier_list;

typedef struct t_struct_declarator_list {
  t_struct_declarator *struct_declarator;
  t_struct_declarator_list *struct_declarator_list;
} t_struct_declarator_list;

typedef struct t_struct_declarator {
    t_constant_expression *constant_expression;
    t_declarator *declarator;
} t_struct_declarator;

typedef struct t_enum_specifier {
  t_token *ENUM;
  t_token *IDENTIFIER;
  t_enumerator_list *enumerator_list;
} t_enum_specifier;

typedef struct t_enumerator_list {
  t_enumerator *enumerator;
  t_enumerator_list *enumerator_list;
} t_enumerator_list;

typedef struct t_enumerator {
  t_enumeration_constant *enumeration_constant;
  t_constant_expression *constant_expression;
} t_enumerator;

typedef struct t_atomic_type_specifier {
  t_token *ATOMIC;
  t_type_name *type_name;
} t_atomic_type_specifier;

typedef struct t_type_qualifier {
  t_token *CONST;
  t_token *RESTRICT;
  t_token *VOLATILE;
  t_token *ATOMIC;
} t_type_qualifier;

typedef struct t_function_specifier {
  t_token *INLINE;
  t_token *NORETURN;
} t_function_specifier;

typedef struct t_alignment_specifier {
  t_token *ALIGNAS;
  t_type_name *type_name;
  t_constant_expression *constant_expression;
} t_alignment_specifier;

typedef struct t_declarator {
  t_pointer *pointer;
  t_direct_declarator *direct_declarator;
} t_declarator;

typedef struct t_pointer {
	t_type_qualifier_list *type_qualifier_list;
	t_pointer *pointer;
} t_pointer;

typedef struct t_type_qualifier_list {
	t_type_qualifier *type_qualifier;
	t_type_qualifier_list *type_qualifier_list;
} t_type_qualifier_list;

typedef struct t_parameter_type_list {
	t_parameter_list *parameter_list;
	t_token *ELLIPSIS;
} t_parameter_type_list;

typedef struct t_parameter_list {
	t_parameter_declaration *parameter_declaration;
	t_parameter_list *parameter_list;
} t_parameter_list;

typedef struct t_parameter_declaration {
	t_declaration_specifiers *declaration_specifiers;
	t_declarator *declarator;
	t_abstract_declarator *abstract_declarator;
} t_parameter_declaration;

typedef struct t_identifier_list{
	t_token *IDENTIFIER;
	t_identifier_list *identifier_list;
} t_identifier_list;

typedef struct t_type_name{
	t_specifier_qualifier_list *specifier_qualifier_list;
	t_abstract_declarator *abstract_declarator;
} t_type_name;

typedef struct t_abstract_declarator {
	t_pointer *pointer;
	t_direct_abstract_declarator *direct_abstract_declarator;
} t_abstract_declarator;

typedef struct t_direct_abstract_declarator {
	t_abstract_declarator *abstract_declarator;
	t_token *STATIC;
	t_type_qualifier_list *type_qualifier_list;
	t_assignment_expression *assignment_expression;
	t_direct_abstract_declarator *direct_abstract_declarator;
	t_parameter_type_list *parameter_type_list;
} t_direct_abstract_declarator;

typedef struct t_initializer {
	t_initializer_list *initializer_list;
	t_assignment_expression *assignment_expression;
} t_initializer;

typedef struct t_initializer_list {
	t_designation *designation;
	t_initializer *initializer;
	t_initializer_list *initializer_list;
} t_initializer_list;

typedef struct t_designation {
	t_designator_list *designator_list;
} t_designation;

typedef struct t_designator_list{
	t_designator *designator;
	t_designator_list *designator_list;
}t_designator_list;


typedef struct t_designator {
	t_constant_expression *constant_expression;
	t_token *IDENTIFIER;
} t_designator;

typedef struct t_static_assert_declaration {
	t_token *STATIC_ASSERT;
	t_constant_expression *constant_expression;
	t_token *STRING_LITERAL;
} t_static_assert_declaration;

typedef struct t_statement {
	t_labeled_statement *labeled_statement;
	t_compound_statement *compound_statement;
	t_expression_statement *expression_statement;
	t_selection_statement *selection_statement;
	t_iteration_statement *iteration_statement;
	t_jump_statement *jump_statement;
} t_statement;

typedef struct t_labeled_statement {
	t_token *IDENTIFIER;
	t_statement *statement;
	t_token *CASE;
	t_constant_expression *constant_expression;
	t_token *DEFAULT;
} t_labeled_statement;

typedef struct t_compound_statement {
	t_block_item_list *block_item_list;
} t_compound_statement;

typedef struct t_block_item_list {
	t_block_item *block_item;
	t_block_item_list *block_item_list;
} t_block_item_list;

typedef struct t_block_item {
	t_declaration *declaration;
	t_statement *statement;
} t_block_item;

typedef struct t_expression_statement {
	t_expression *expression;
} t_expression_statement;

typedef struct t_selection_statement{
	t_token *IF;
	t_expression *expression;
	t_statement *statement;
	t_token *ELSE;
	t_token *SWITCH;
} t_selection_statement;

typedef struct t_iteration_statement {
  t_whileLoop *whileLoop;
  t_doWhileLoop *doWhileLoop;
  t_forLoop *forLoop;
} t_iteration_statement;

typedef struct t_doWhileLoop {
  t_statement *statement;
  t_whileLoop *whileLoop;
  t_expression *expression;
} t_doWhileLoop;

typedef struct t_whileLoop {
  t_expression *expression;
  t_statement *statement;
} t_whileLoop;

typedef struct t_forLoop {
  t_token *FOR;
  t_declaration *declaration;
  t_expression_statement *expression_statementFirst;
  t_expression_statement *expression_statementSecond;
  t_expression *expression;
  t_statement *statement;
} t_forLoop;

typedef struct t_jump_statement {
  t_token *GOTO;
  t_token *CONTINUE;
  t_token *BREAK;
  t_token *RETURN;
  t_expression *expression;
} t_jump_statement;

typedef struct t_translation_unit {
  t_external_declaration *external_declaration;
  t_translation_unit *translation_unit;
} t_translation_unit;

typedef struct t_external_declaration {
  t_function_definition *function_definition;
  t_declaration *declaration;
} t_external_declaration;

typedef struct t_function_definition{
  t_declaration_specifiers *declaration_specifiers;
  t_declarator *declarator;
  t_declaration_list *declaration_list;
  t_compound_statement *compound_statement;
} t_function_definition;

typedef struct t_declaration_list {
  t_declaration *declaration;
  t_declaration_list *declaration_list;
} t_declaration_list;
