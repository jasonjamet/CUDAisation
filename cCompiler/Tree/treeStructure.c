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
